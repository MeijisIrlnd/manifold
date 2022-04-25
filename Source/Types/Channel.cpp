/*
  ==============================================================================

    Channel.cpp
    Created: 24 Apr 2022 9:25:47pm
    Author:  Syl

  ==============================================================================
*/

#include "InternalChannel.h"

Manifold::Audio::InternalChannel::InternalChannel(const int internalId, const std::string& name) : 
    m_internalId(internalId), 
    m_name(name)
{
}

void Manifold::Audio::InternalChannel::rename(const std::string& newName)
{
    m_name = newName;
}
