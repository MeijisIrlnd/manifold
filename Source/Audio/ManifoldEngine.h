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
#include "../Types/InternalChannel.h"

using Graph = juce::AudioProcessorGraph;
using Node = Graph::Node;
using Tree = juce::AudioProcessorValueTreeState;
using namespace Manifold::Audio::Core;
namespace Manifold
{
    namespace Audio
    {
        class ManifoldEngine
        {
        public: 
            ManifoldEngine();
            ~ManifoldEngine();

            void initialiseGraph();
            void bindUICallbacks();
            MANIFOLD_INLINE void connectAudioNodes(int numChannels) {
                
                for (auto channel = 0; channel < numChannels; channel++) {
                    m_graph.addConnection({ {m_audioInputNode->nodeID, channel}, {m_audioDriver->nodeID, channel}  });
                    m_graph.addConnection({ { m_audioDriver->nodeID, channel}, {m_audioOutputNode->nodeID, channel} });
                }
            }
            
            MANIFOLD_INLINE UIListener* getUIListener() { return &m_uiListener; }
            MANIFOLD_INLINE PositionTracker* getPositionTracker() { return &m_positionTracker; }

            InternalChannel* createChannel();
        private: 
            juce::AudioDeviceManager m_deviceManager;
            juce::AudioProcessorPlayer m_player;
            PositionTracker m_positionTracker;
            Graph m_graph;
            Node::Ptr m_audioInputNode;
            Node::Ptr m_audioOutputNode;

            Node::Ptr m_audioDriver;
            Tree m_tree;
            UIListener m_uiListener;

            std::unordered_map<int, std::unique_ptr<InternalChannel> > m_channelList;
            unsigned int m_nextAvailableId = 0;
        };
    }
}