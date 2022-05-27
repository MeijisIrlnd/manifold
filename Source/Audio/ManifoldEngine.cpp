/*
  ==============================================================================

    Engine.cpp
    Created: 22 Apr 2022 1:45:14am
    Author:  Syl

  ==============================================================================
*/

#include "ManifoldEngine.h"

namespace Manifold
{
    namespace Audio
    {
        std::unique_ptr<ManifoldEngine> ManifoldEngine::m_instance{ nullptr };
        std::mutex ManifoldEngine::m_mutex;

        ManifoldEngine::ManifoldEngine() : 
            m_tree(m_graph, nullptr, {"Params"}, { })
        {
            auto inputDevice = juce::MidiInput::getDefaultDevice();
            auto outputDevice = juce::MidiOutput::getDefaultDevice();
            m_pluginFormatManager.addDefaultFormats();
            m_graph.enableAllBuses();
            m_deviceManager.initialiseWithDefaultDevices(2, 2);
            m_deviceManager.addAudioCallback(&m_player);
            m_deviceManager.setMidiInputDeviceEnabled(inputDevice.identifier, true);
            m_deviceManager.addMidiInputDeviceCallback(inputDevice.identifier, &m_player);
            m_deviceManager.setDefaultMidiOutputDevice(outputDevice.identifier);
            initialiseGraph();
            bindUICallbacks();
            m_player.setProcessor(&m_graph);
            MANIFOLD_UNUSED auto& collector = m_player.getMidiMessageCollector();
            scanForVsts();
        }

        ManifoldEngine::~ManifoldEngine() {
            m_deviceManager.removeAudioCallback(&m_player);
        }

        ManifoldEngine* ManifoldEngine::getInstance()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr) {
                m_instance.reset(new ManifoldEngine);
            }
            return m_instance.get();
        }

        void ManifoldEngine::shutdown()
        {
            m_instance->m_deviceManager.removeAudioCallback(&m_instance->m_player);
            m_instance.reset(nullptr);
        }

        void ManifoldEngine::initialiseGraph()
        {
            m_graph.clear();
            m_midiInputNode = m_graph.addNode(std::make_unique<Graph::AudioGraphIOProcessor>(Graph::AudioGraphIOProcessor::midiInputNode));
            m_midiOutputNode = m_graph.addNode(std::make_unique<Graph::AudioGraphIOProcessor>(Graph::AudioGraphIOProcessor::midiOutputNode));
            m_audioInputNode = m_graph.addNode(std::make_unique<Graph::AudioGraphIOProcessor>(Graph::AudioGraphIOProcessor::audioInputNode));
            m_audioDriver = m_graph.addNode(std::make_unique<AudioDriver>(m_positionTracker));
            m_audioOutputNode = m_graph.addNode(std::make_unique<Graph::AudioGraphIOProcessor>(Graph::AudioGraphIOProcessor::audioOutputNode));
            connectAudioNodes(2);
            connectMidiNodes(2);
            
        }

        void ManifoldEngine::bindUICallbacks()
        {
            m_uiListener.m_mappings.emplace(std::make_pair(
                FUNCTION::TRANSPORT_PLAY,
                [this]() { 
                    DBG("Play called");
                    m_positionTracker.toggle(true);
                }
            ));

            m_uiListener.m_mappings.emplace(std::make_pair(
                FUNCTION::TRANSPORT_PAUSE,
                [this]() {
                    DBG("Pause called");
                    m_positionTracker.toggle(false);
                }
            ));

            m_uiListener.m_mappings.emplace(std::make_pair(
                FUNCTION::TRANSPORT_STOP,
                [this]() { 
                    DBG("Stop called");
                    m_positionTracker.toggle(false);
                    m_positionTracker = 0;
                }
            ));
        }

        void ManifoldEngine::scanForVsts()
        {
            m_vsts.clear();
            for (auto& dir : juce::RangedDirectoryIterator(juce::File(VST_PATH), true, "*.vst3,*.dll", juce::File::findFiles))
            {
                for (auto i = 0; i < m_pluginFormatManager.getNumFormats(); i++) {
                    m_vsts.scanAndAddFile(dir.getFile().getFullPathName(), true, m_vstDescriptions, *m_pluginFormatManager.getFormat(i));
                }
            }
        }

        void ManifoldEngine::createChannel(CHANNEL_TYPE t, int sourcePluginIndex)
        {
            bool channelCreated = false;
            int currentId = m_nextAvailableId;
            std::string currentChannelName = "Channel " + std::to_string(currentId);
            ++m_nextAvailableId;
            std::unique_ptr<InternalChannel> ch;
            if (t == CHANNEL_TYPE::AUDIO) {
                ch.reset(dynamic_cast<InternalChannel*>(new AudioChannel(currentId, currentChannelName)));
            }
            else {
                ch.reset(dynamic_cast<InternalChannel*>(new MidiChannel(currentId, currentChannelName)));
            }
            
            m_channelList.emplace(
                std::make_pair(currentId, std::move(ch))
            );
            InternalChannel* current = m_channelList[currentId].get();
            if (t == CHANNEL_TYPE::AUDIO) {
                std::unique_ptr<AudioChannelProcessor> currentProcessor(new AudioChannelProcessor(dynamic_cast<AudioChannel*>(current)));
                Node::Ptr handle = m_graph.addNode(std::move(currentProcessor));
                m_channelNodes.emplace(std::make_pair(current->getId(), handle));
                std::vector<juce::AudioPluginInstance*> temp{8};
                m_channelInserts.emplace(current->getId(), std::move(temp));
                connectAudioNodes(2);
                channelCreated = true;
            }
            else {
                if (sourcePluginIndex != -1) {
                    std::unique_ptr<MidiChannelProcessor> currentProcessor(new MidiChannelProcessor(current));
                    Node::Ptr handle = m_graph.addNode(std::move(currentProcessor));
                    m_channelNodes.emplace(std::make_pair(current->getId(), handle));
                    auto desc = m_vsts.getTypes()[sourcePluginIndex];
                    auto sr = m_deviceManager.getAudioDeviceSetup().sampleRate;
                    auto bufferSize = m_deviceManager.getAudioDeviceSetup().bufferSize;
                    std::function<void(std::unique_ptr<juce::AudioPluginInstance>, const juce::String&)> loadedCallback =
                        [this, handle](std::unique_ptr<juce::AudioPluginInstance> instance, MANIFOLD_UNUSED const juce::String& errorMessage)
                    {
                        MidiChannelProcessor* proc = dynamic_cast<MidiChannelProcessor*>(handle->getProcessor());
                        proc->loadSourcePlugin(std::move(instance));

                    };
                    m_pluginFormatManager.createPluginInstanceAsync(desc, sr, bufferSize, loadedCallback);
                    connectAudioNodes(2);
                    connectMidiNodes(2);
                    channelCreated = true;
                }
            }

            if (channelCreated) {
                for (auto& l : m_listeners) {
                    if (l != nullptr) {
                        l->onChannelCreated(current);
                    }
                }
            }
        }
        void ManifoldEngine::deleteChannel(InternalChannel* toDelete)
        {
            for (auto& l : m_listeners) {
                if (l != nullptr) { l->onChannelDeleted(toDelete); }
            }

        }

        void ManifoldEngine::loadPlugin(MANIFOLD_UNUSED const int channelId, MANIFOLD_UNUSED const int slot, int selectedIndex)
        {
            auto desc = m_vsts.getTypes()[selectedIndex];
            auto sr = m_deviceManager.getAudioDeviceSetup().sampleRate;
            auto bufferSize = m_deviceManager.getAudioDeviceSetup().bufferSize;
            std::function<void(std::unique_ptr<juce::AudioPluginInstance>, const juce::String&)> loadedCallback = 
            [this, channelId, slot] (std::unique_ptr<juce::AudioPluginInstance> instance, MANIFOLD_UNUSED const juce::String& errorMessage) {
                m_channelInserts[channelId][slot] = instance.get();
                BaseChannelProcessor* current = dynamic_cast<BaseChannelProcessor*>(m_channelNodes[channelId]->getProcessor());
                current->loadPlugin(slot, std::move(instance));
            };

            m_pluginFormatManager.createPluginInstanceAsync(desc, sr, bufferSize, loadedCallback);
        }

        void ManifoldEngine::createEditorForPlugin(const int channelId, const int slot)
        {
            if (m_channelInserts.find(channelId) != m_channelInserts.end()) {
                if (m_channelInserts[channelId][slot] != nullptr) {
                    for (auto& l : m_listeners) {
                        if (l != nullptr) {
                            l->onPluginUIOpened(m_channelInserts[channelId][slot]);
                        }
                    }
                }
            }
        }
    }
}

