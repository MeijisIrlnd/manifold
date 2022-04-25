/*
  ==============================================================================

    Channel.cpp
    Created: 24 Apr 2022 9:25:47pm
    Author:  Syl

  ==============================================================================
*/

#include "InternalChannel.h"

Manifold::Audio::InternalChannel::InternalChannel(int internalId, std::string name) : 
    m_internalId(internalId), 
    m_name(name)
{
}

Manifold::Audio::InternalChannel::InternalChannel(const InternalChannel& other) : 
    m_internalId(other.m_internalId),
    m_name(other.m_name)
{
}

void Manifold::Audio::InternalChannel::rename(const std::string& newName)
{
    m_name = newName;
}
