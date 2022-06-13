/*
  ==============================================================================

    ManifoldEngine.h
    Created: 22 Apr 2022 1:45:14am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <ranges>
#include <JuceHeader.h>
#include "../Macros.h"
#include "../Utils/UIListener.h"
#include "Core/PositionTracker.h"
#include "Core/AudioDriver.h"
#include "Core/AudioChannelProcessor.h"
#include "Core/MidiChannelProcessor.h"
#include "Core/GroupChannelProcessor.h"
#include "Core/VolumeNodeProcessor.h"
#include "../UI/Components/Windows/WindowManager.h"
#include "../Types/Channel/Channel.h"
#include "../Types/TrackNode.h"
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
            
            MANIFOLD_INLINE UIListener* getUIListener() { return &m_uiListener; }
            MANIFOLD_INLINE PositionTracker* getPositionTracker() { return &m_positionTracker; }
            MANIFOLD_INLINE juce::AudioDeviceManager& getDeviceManager() { return m_deviceManager; }
            std::unordered_map<int, std::unique_ptr<InternalChannel> >& getChannelList() { return m_channelList; }
            std::unordered_map<int, InternalChannel*> getChannelsOfType(CHANNEL_TYPE t);
            MANIFOLD_INLINE juce::KnownPluginList& getPluginList() { return m_plugins; }
            juce::Array<juce::PluginDescription> getFilteredDescriptions(bool findInstruments) {
                juce::Array<juce::PluginDescription> current = m_plugins.getTypes();
                std::function<bool(const juce::PluginDescription&)> predicate = [findInstruments](const juce::PluginDescription& el) {
                    return findInstruments ? !el.isInstrument : el.isInstrument;
                };
                current.removeIf(predicate);
                return current;
            }
            MANIFOLD_INLINE const juce::OwnedArray<juce::PluginDescription>& getDescriptions() { return m_pluginDescriptions; }
            void createChannel(CHANNEL_TYPE t, juce::PluginDescription desc = {});
            void deleteChannel(InternalChannel* toDelete);

            void loadPlugin(const int channelId, const int slot, juce::PluginDescription desc);
            void createEditorForPlugin(const int channelId, const int slot);
            void createEditorForMidiChannelPlugin(const int channelId);
            void connectNodes(const int nodeA, const int nodeB = -1);
        private: 
            static std::mutex m_mutex;
            //std::unordered_map<std::string, std::string> m_vsts;
            juce::AudioPluginFormatManager m_pluginFormatManager;
            juce::OwnedArray<juce::PluginDescription> m_pluginDescriptions;
            juce::KnownPluginList m_plugins;
            juce::AudioDeviceManager m_deviceManager;
            juce::AudioProcessorPlayer m_player;
            PositionTracker m_positionTracker;
            Graph m_graph;
            Node::Ptr m_midiInputNode;
            Node::Ptr m_midiOutputNode;
            Node::Ptr m_audioInputNode;
            Node::Ptr m_audioOutputNode;
            Node::Ptr m_audioDriver;
            std::unordered_map<int, TrackNode> m_channelNodes;
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