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
    m_channelType(channelType)
{
}

Manifold::Audio::InternalChannel::InternalChannel(const InternalChannel& other) : 
    m_internalId(other.m_internalId),
    m_name(other.m_name),
    m_channelType(other.m_channelType)
{
}

Manifold::Audio::InternalChannel::~InternalChannel()
{
}

void Manifold::Audio::InternalChannel::rename(const std::string& newName)
{
    m_name = newName;
}
