/*
  ==============================================================================

    Channel.cpp
    Created: 24 Apr 2022 9:25:47pm
    Author:  Syl

  ==============================================================================
*/

#include "InternalChannel.h"

Manifold::Audio::InternalChannel::InternalChannel(int internalId, std::string name, CHANNEL_TYPE channelType) : 
    m_internalId(internalId), 
    m_name(name),
    m_channelType(channelType), 
    m_valueTree({ std::to_string(m_internalId) }, {})
{
    std::string groupId = std::to_string(m_internalId);
    m_valueTree.setProperty({ groupId + "_volume" }, 1, nullptr);
    m_valueTree.setProperty({ groupId + "_pan" }, 0.5, nullptr);
    m_valueTree.setProperty({ groupId + "_mute" }, false, nullptr);
    m_valueTree.setProperty({ groupId + "_solo" }, false, nullptr);
    
}

Manifold::Audio::InternalChannel::InternalChannel(const InternalChannel& other) : 
    m_internalId(other.m_internalId),
    m_name(other.m_name),
    m_channelType(other.m_channelType)
{
    std::string groupId = std::to_string(m_internalId);
    m_valueTree.setProperty({ groupId + "_volume" }, 1, nullptr);
    m_valueTree.setProperty({ groupId + "_pan" }, 0.5, nullptr);
    m_valueTree.setProperty({ groupId + "_mute" }, false, nullptr);
    m_valueTree.setProperty({ groupId + "_solo" }, false, nullptr);
    
}

Manifold::Audio::InternalChannel::~InternalChannel()
{
}

void Manifold::Audio::InternalChannel::rename(const std::string& newName)
{
    m_name = newName;
    m_hasRenamed = true;
}
