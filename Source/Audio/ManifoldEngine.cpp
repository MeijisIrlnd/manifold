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
            m_graph.enableAllBuses();
            m_deviceManager.initialiseWithDefaultDevices(2, 2);
            m_deviceManager.addAudioCallback(&m_player);
            initialiseGraph();
            bindUICallbacks();
            m_player.setProcessor(&m_graph);
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
            m_audioInputNode = m_graph.addNode(std::make_unique<Graph::AudioGraphIOProcessor>(Graph::AudioGraphIOProcessor::audioInputNode));
            m_audioDriver = m_graph.addNode(std::make_unique<AudioDriver>(m_positionTracker));
            m_audioOutputNode = m_graph.addNode(std::make_unique<Graph::AudioGraphIOProcessor>(Graph::AudioGraphIOProcessor::audioOutputNode));
            connectAudioNodes(2);
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
                m_vsts.emplace(std::make_pair(dir.getFile().getFileNameWithoutExtension().toStdString(),
                    dir.getFile().getFullPathName().toStdString()));
            }
        }

        void ManifoldEngine::createChannel(CHANNEL_TYPE t)
        {
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
            for (auto& l : m_listeners) {
                if (l != nullptr) {
                    l->onChannelCreated(current);
                }
            }   
        }
        void ManifoldEngine::deleteChannel(InternalChannel* toDelete)
        {
            for (auto& l : m_listeners) {
                if (l != nullptr) { l->onChannelDeleted(toDelete); }
            }

        }
        void ManifoldEngine::loadVst(MANIFOLD_UNUSED const int channelId, MANIFOLD_UNUSED const int slot, const std::string& key)
        {
            std::string vstPath = m_vsts[key];
            std::stringstream stream;
            stream << "ID: " << channelId << " Slot: " << slot << " Path: " << vstPath;
            DBG(stream.str());
            // some other stuf..
        }
    }
}

