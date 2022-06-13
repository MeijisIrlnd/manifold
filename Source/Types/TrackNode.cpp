/*
  ==============================================================================

    TrackNode.cpp
    Created: 13 Jun 2022 12:35:25am
    Author:  Syl

  ==============================================================================
*/

#include "TrackNode.h"

Manifold::Audio::TrackNode::TrackNode(InternalChannel* associatedChannel, Node::Ptr top, Node::Ptr volume) : 
    m_associatedChannel(associatedChannel), m_topNode(top), m_volumeNode(volume)
{
    for (auto i = 0; i < 2; i++) {
        Connection current({ {m_topNode->nodeID, i}, {m_volumeNode->nodeID} });
        m_internalConnections.emplace_back(current);
    }
}



Manifold::Audio::TrackNode::TrackNode(InternalChannel* associatedChannel, Node::Ptr vst, Node::Ptr top, Node::Ptr volume) : 
    m_associatedChannel(associatedChannel), m_vstNode(vst), m_topNode(top), m_volumeNode(volume) 
{
    for (auto i = 0; i < 2; i++) {
        Connection vstConn({ {m_vstNode->nodeID, i}, {m_topNode->nodeID, i} });
        Connection current({ {m_topNode->nodeID, i}, {m_volumeNode->nodeID} });
        m_internalConnections.emplace_back(vstConn);
        m_internalConnections.emplace_back(current);
    }
}

Manifold::Audio::TrackNode::TrackNode(const TrackNode& other) : 
    m_associatedChannel(other.m_associatedChannel), 
    m_vstNode(other.m_vstNode),
    m_topNode(other.m_topNode), 
    m_volumeNode(other.m_volumeNode), 
    m_internalConnections(other.m_internalConnections)
{
}

Manifold::Audio::TrackNode::TrackNode(TrackNode&& other) : 
    m_associatedChannel(other.m_associatedChannel),
    m_vstNode(other.m_vstNode),
    m_topNode(other.m_topNode),
    m_volumeNode(other.m_volumeNode),
    m_internalConnections(other.m_internalConnections)
{
}

