/*
  ==============================================================================

    TrackNode.h
    Created: 13 Jun 2022 12:35:25am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
#include "Channel/InternalChannel.h"
#include "../Audio/Core/BaseChannelProcessor.h"
using Node = juce::AudioProcessorGraph::Node;
using Connection = juce::AudioProcessorGraph::Connection;
namespace Manifold::Audio
{
    class TrackNode
    {
    public: 
        TrackNode(InternalChannel* associatedChannel, Node::Ptr top, Node::Ptr volume);
        TrackNode(InternalChannel* associatedChannel, Node::Ptr vst, Node::Ptr top, Node::Ptr volume);
        TrackNode(const TrackNode& other);
        TrackNode(TrackNode&& other);
        MANIFOLD_INLINE CHANNEL_TYPE getType() { return m_associatedChannel->getChannelType(); }
        MANIFOLD_INLINE Node::Ptr& getVstNode() { return m_vstNode; }
        MANIFOLD_INLINE Node::Ptr& getInputNode() { return m_topNode; }
        MANIFOLD_INLINE Node::Ptr& getOutputNode() { return m_volumeNode; }
        MANIFOLD_INLINE Node::Ptr& getSendNode(bool pfl) { return pfl ? m_topNode : m_volumeNode; }
        MANIFOLD_INLINE std::vector<Connection>& getInternalConnections() { return m_internalConnections; }
        MANIFOLD_INLINE void loadPlugin(int idx, std::unique_ptr<juce::AudioPluginInstance>&& plugin) {
            auto* current = dynamic_cast<Core::BaseChannelProcessor*>(m_topNode->getProcessor());
            current->loadPlugin(idx, std::move(plugin));
        }
    private: 
        InternalChannel* m_associatedChannel;
        Node::Ptr m_vstNode, m_topNode, m_volumeNode;
       
        std::vector<Connection> m_internalConnections;

        
    };
}