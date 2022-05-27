/*
  ==============================================================================

    ManifoldEngine.h
    Created: 22 Apr 2022 1:45:14am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
#include "../Utils/UIListener.h"
#include "Core/PositionTracker.h"
#include "Core/AudioDriver.h"
#include "Core/AudioChannelProcessor.h"
#include "Core/MidiChannelProcessor.h"
#include "../Types/Channel/Channel.h"
#include "../Settings/Pathing.h"
#include <LeakBacktracer.h>
using Graph = juce::AudioProcessorGraph;
using Node = Graph::Node;
using Tree = juce::AudioProcessorValueTreeState;
using namespace Manifold::Audio::Core;
namespace Manifold
{
    namespace Audio
    {
        struct EngineListener
        {
            virtual ~EngineListener() {}
            virtual void onChannelCreated(MANIFOLD_UNUSED InternalChannel* newChannel) {};
            virtual void onChannelDeleted(MANIFOLD_UNUSED InternalChannel* toDelete) {};
            virtual void onPluginUIOpened(MANIFOLD_UNUSED juce::AudioProcessor* processor) {}
        };

        class ManifoldEngine
        {
        protected: 
            ManifoldEngine();
        public: 
            ~ManifoldEngine();
            ManifoldEngine(ManifoldEngine& other) = delete;
            void operator=(const ManifoldEngine& other) = delete;
            static ManifoldEngine* getInstance();
            static void shutdown();
            void initialiseGraph();
            void bindUICallbacks();
            void scanForVsts();
            MANIFOLD_INLINE void addListener(EngineListener* newListener) { m_listeners.push_back(newListener); }
            MANIFOLD_INLINE void removeListener(EngineListener* toRemove) {
                auto it = std::find(m_listeners.begin(), m_listeners.end(), toRemove);
                if (it != m_listeners.end()) {
                    m_listeners.erase(it);
                }
            }

            MANIFOLD_INLINE void connectAudioNodes(int numChannels) {
                
                for (auto channel = 0; channel < numChannels; channel++) {
                    for (auto& c : m_channelNodes) {
                        m_graph.addConnection({ {m_audioInputNode->nodeID, channel}, {c.second->nodeID, channel} });
                        m_graph.addConnection({ { c.second->nodeID, channel}, { m_audioOutputNode->nodeID, channel} });
                    }
                }
            }

            MANIFOLD_INLINE void connectMidiNodes(int numChannels) {
                for (auto channel = 0; channel < numChannels; channel++) {
                    for (auto& c : m_channelNodes) {
                        BaseChannelProcessor* current = dynamic_cast<BaseChannelProcessor*>(c.second->getProcessor());
                        if (current->getType() == CHANNEL_TYPE::MIDI) {
                            m_graph.addConnection({{ m_midiInputNode->nodeID, channel}, {c.second->nodeID, channel}});
                            m_graph.addConnection({ {c.second->nodeID, channel}, {m_midiOutputNode->nodeID, channel} });
                        }
                    }
                }
            }
            
            MANIFOLD_INLINE UIListener* getUIListener() { return &m_uiListener; }
            MANIFOLD_INLINE PositionTracker* getPositionTracker() { return &m_positionTracker; }
            std::unordered_map<int, std::unique_ptr<InternalChannel> >& getChannelList() { return m_channelList; }
            MANIFOLD_INLINE juce::KnownPluginList& getVstList() { return m_vsts; }
            MANIFOLD_INLINE const juce::OwnedArray<juce::PluginDescription>& getVstDescriptions() { return m_vstDescriptions; }
            void createChannel(CHANNEL_TYPE t, int sourcePluginInstrument = -1);
            void deleteChannel(InternalChannel* toDelete);

            void loadPlugin(const int channelId, const int slot, int selectedIndex);
            void createEditorForPlugin(const int channelId, const int slot);
        private: 
            static std::mutex m_mutex;
            //std::unordered_map<std::string, std::string> m_vsts;
            juce::AudioPluginFormatManager m_pluginFormatManager;
            juce::OwnedArray<juce::PluginDescription> m_vstDescriptions;
            juce::KnownPluginList m_vsts;
            juce::AudioDeviceManager m_deviceManager;
            juce::AudioProcessorPlayer m_player;
            PositionTracker m_positionTracker;
            Graph m_graph;
            Node::Ptr m_midiInputNode;
            Node::Ptr m_midiOutputNode;
            Node::Ptr m_audioInputNode;
            Node::Ptr m_audioOutputNode;
            Node::Ptr m_audioDriver;
            std::unordered_map<int, Node::Ptr> m_channelNodes;
            std::unordered_map<int, std::vector<juce::AudioPluginInstance*> > m_channelInserts;
            Tree m_tree;
            UIListener m_uiListener;
            std::unordered_map<int, std::unique_ptr<InternalChannel> > m_channelList;
            unsigned int m_nextAvailableId = 0;
            std::vector<EngineListener*> m_listeners;
            AdvancedLeakDetector m_leakDetector;
            static std::unique_ptr<ManifoldEngine> m_instance;
        };
    }
}