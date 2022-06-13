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
            m_plugins.clear();
            for (auto& dir : juce::RangedDirectoryIterator(juce::File(VST_PATH), true, "*.vst3,*.dll", juce::File::findFiles))
            {
                for (auto i = 0; i < m_pluginFormatManager.getNumFormats(); i++) {
                    m_plugins.scanAndAddFile(dir.getFile().getFullPathName(), true, m_pluginDescriptions, *m_pluginFormatManager.getFormat(i));
                }
            }
        }

        std::unordered_map<int, InternalChannel*> ManifoldEngine::getChannelsOfType(CHANNEL_TYPE t)
        {
            std::unordered_map<int, InternalChannel*> retval;
            for (auto it = m_channelList.begin(); it != m_channelList.end(); it++) {
                if (it->second->getChannelType() == t) {
                    retval.emplace(std::make_pair(it->first, it->second.get()));
                }
            }
            return retval;
        }

        void ManifoldEngine::createChannel(CHANNEL_TYPE t, juce::PluginDescription desc)
        {
            bool channelCreated = false;
            int currentId = m_nextAvailableId;
            std::string currentChannelName = "Channel " + std::to_string(currentId);
            ++m_nextAvailableId;
            std::unique_ptr<InternalChannel> ch;
            switch (t) {
            case CHANNEL_TYPE::AUDIO: 
                ch.reset(dynamic_cast<InternalChannel*>(new AudioChannel(currentId, currentChannelName)));
                break;
            case CHANNEL_TYPE::MIDI: 
                ch.reset(dynamic_cast<InternalChannel*>(new MidiChannel(currentId, currentChannelName)));
                break;
            case CHANNEL_TYPE::GROUP: 
                ch.reset(dynamic_cast<InternalChannel*>(new GroupChannel(currentId, currentChannelName)));
                break;
            }

            m_channelList.emplace(
                std::make_pair(currentId, std::move(ch))
            );
            InternalChannel* current = m_channelList[currentId].get();

            if (t == CHANNEL_TYPE::AUDIO) {
                auto* currentAudioChannel = dynamic_cast<AudioChannel*>(current);
                std::unique_ptr<AudioChannelProcessor> currentProcessor(new AudioChannelProcessor(dynamic_cast<AudioChannel*>(current)));
                std::unique_ptr<VolumeNodeProcessor> volumeProcessor(new VolumeNodeProcessor(current));

                Node::Ptr topHandle = m_graph.addNode(std::move(currentProcessor));
                Node::Ptr volumeHandle = m_graph.addNode(std::move(volumeProcessor));
                TrackNode trackNode(current, topHandle, volumeHandle);
                m_channelNodes.emplace(std::make_pair(current->getId(), trackNode));
                std::vector<juce::AudioPluginInstance*> temp{8};
                m_channelInserts.emplace(current->getId(), std::move(temp));
                using Connection = juce::AudioProcessorGraph::Connection;
                for (auto& intcon : trackNode.getInternalConnections()) {
                    m_graph.addConnection(intcon);
                }

                for (auto channel = 0; channel < 2; channel++) {
                    auto ip = trackNode.getInputNode();
                    auto op = trackNode.getOutputNode();
                    Connection input({ { m_audioInputNode->nodeID, channel}, {ip->nodeID, channel} });
                    Connection output({ { op->nodeID, channel}, {m_audioOutputNode->nodeID, channel} });
                    m_graph.addConnection(input);
                    currentAudioChannel->addInputConnection(input);
                    m_graph.addConnection(output);
                    currentAudioChannel->addOutputConnection(output);
                }
                channelCreated = true;
            }
            else if(t == CHANNEL_TYPE::MIDI) {
                auto sr = m_deviceManager.getAudioDeviceSetup().sampleRate;
                auto bufferSize = m_deviceManager.getAudioDeviceSetup().bufferSize;
                std::function<void(std::unique_ptr<juce::AudioPluginInstance>, const juce::String&)> loadedCallback =
                    [this, sr, bufferSize, current](std::unique_ptr<juce::AudioPluginInstance> instance, MANIFOLD_UNUSED const juce::String& errorMessage)
                {
                    DBG(errorMessage);
                    auto* currentMidiChannel = dynamic_cast<MidiChannel*>(current);
                    instance->enableAllBuses();
                    std::unique_ptr<MidiChannelProcessor> currentProcessor(new MidiChannelProcessor(current));
                    std::unique_ptr<VolumeNodeProcessor> volumeProcessor(new VolumeNodeProcessor(current));
                    currentProcessor->enableAllBuses();
                    volumeProcessor->enableAllBuses();
                    Node::Ptr vstHandle = m_graph.addNode(std::move(instance));
                    Node::Ptr topHandle = m_graph.addNode(std::move(currentProcessor));
                    Node::Ptr volHandle = m_graph.addNode(std::move(volumeProcessor));
                    using Connection = juce::AudioProcessorGraph::Connection;
                    TrackNode trackNode(current, vstHandle, topHandle, volHandle);
                    for (auto& conn : trackNode.getInternalConnections()) {
                        m_graph.addConnection(conn);
                    }
                    for (auto channel = 0; channel < 2; channel++) {
                        Connection output({ { trackNode.getInputNode()->nodeID, channel }, { m_audioOutputNode->nodeID, channel } });
                        m_graph.addConnection(output);
                        currentMidiChannel->addOutputConnection(output);
                    }
                    m_channelNodes.emplace(std::make_pair(current->getId(), trackNode));
                    std::vector<juce::AudioPluginInstance*> temp{ 8 };
                    m_channelInserts.emplace(current->getId(), std::move(temp));
                };
                m_pluginFormatManager.createPluginInstanceAsync(desc, sr, bufferSize, loadedCallback);
                channelCreated = true;
            }
            else if (t == CHANNEL_TYPE::GROUP) {
                std::unique_ptr<GroupChannelProcessor> currentProcessor(new GroupChannelProcessor(dynamic_cast<GroupChannel*>(current)));
                std::unique_ptr<VolumeNodeProcessor> volumeProcessor(new VolumeNodeProcessor(current));
                currentProcessor->enableAllBuses();
                auto* currentGroupChannel = dynamic_cast<GroupChannel*>(current);
                Node::Ptr topHandle = m_graph.addNode(std::move(currentProcessor));
                Node::Ptr volHandle = m_graph.addNode(std::move(volumeProcessor));
                TrackNode trackNode(current, topHandle, volHandle);
                for (auto& conn : trackNode.getInternalConnections()) {
                    m_graph.addConnection(conn);
                }
                using Connection = juce::AudioProcessorGraph::Connection;
                for (auto channel = 0; channel < 2; channel++) {
                    Connection output({ {trackNode.getOutputNode()->nodeID, channel}, {m_audioOutputNode->nodeID, channel} });
                    m_graph.addConnection(output);
                    currentGroupChannel->addOutputConnection(output);
                }
                m_channelNodes.emplace(current->getId(), trackNode);
                std::vector<juce::AudioPluginInstance*> temp{ 8 };
                m_channelInserts.emplace(current->getId(), std::move(temp));
                channelCreated = true;
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

        void ManifoldEngine::loadPlugin(const int channelId, const int slot, juce::PluginDescription desc)
        {
            auto sr = m_deviceManager.getAudioDeviceSetup().sampleRate;
            auto bufferSize = m_deviceManager.getAudioDeviceSetup().bufferSize;
            std::function<void(std::unique_ptr<juce::AudioPluginInstance>, const juce::String&)> loadedCallback = 
            [this, channelId, slot] (std::unique_ptr<juce::AudioPluginInstance> instance, MANIFOLD_UNUSED const juce::String& errorMessage) {
                m_channelInserts[channelId][slot] = instance.get();
                m_channelNodes.at(channelId).loadPlugin(slot, std::move(instance));
            };

            m_pluginFormatManager.createPluginInstanceAsync(desc, sr, bufferSize, loadedCallback);
        }

        void ManifoldEngine::createEditorForPlugin(const int channelId, const int slot)
        {
            if (m_channelInserts.find(channelId) != m_channelInserts.end()) {
                if (m_channelInserts[channelId][slot] != nullptr) {
                    GET_WINDOW_MANAGER()->addPluginWindow(m_channelInserts[channelId][slot]);
                }
            }
        }

        void ManifoldEngine::createEditorForMidiChannelPlugin(const int channelId)
        {
            auto it = m_channelNodes.find(channelId);
            if (it != m_channelNodes.end()) {
                auto& vstNode = m_channelNodes.at(channelId).getVstNode();
                GET_WINDOW_MANAGER()->addPluginWindow(vstNode->getProcessor());
            }
        }


        void ManifoldEngine::connectNodes(const int nodeA, const int nodeB)
        {
            using Connection = juce::AudioProcessorGraph::Connection;
            if (nodeB == -1) {
                auto* channelA = m_channelList.at(nodeA).get();
                auto& connections = channelA->getOutputConnections();
                for (auto& connection : connections) {
                    m_graph.removeConnection(connection);
                }
                connections.clear();
                // Connect to output..
                for (auto channel = 0; channel < 2; channel++) {
                    Connection current({ {m_channelNodes.at(nodeA).getOutputNode()->nodeID, channel}, {m_audioOutputNode->nodeID, channel}});
                    m_graph.addConnection(current);
                    channelA->addOutputConnection(current);
                }
            }
            else {
                auto* channelA = m_channelList.at(nodeA).get();
                auto* channelB = dynamic_cast<GroupChannel*>(m_channelList.at(nodeB).get());
                // Disconnect channel A's outputs
                auto& channelAOuts = channelA->getOutputConnections();
                for (auto& outputConnection : channelAOuts) {
                    m_graph.removeConnection(outputConnection);
                }
                channelAOuts.clear();
                // Make the new connections, and plug them into B 
                for (auto channel = 0; channel < 2; channel++) {
                    Connection current({ {m_channelNodes.at(nodeA).getOutputNode()->nodeID, channel}, {m_channelNodes.at(nodeB).getInputNode()->nodeID, channel}});
                    m_graph.addConnection(current);
                    channelA->addOutputConnection(current);
                    channelB->addInputConnection(nodeA, current);
                }
            }
        }


    }
}

