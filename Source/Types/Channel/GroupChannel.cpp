/*
  ==============================================================================

    GroupChannel.cpp
    Created: 12 Jun 2022 7:06:03pm
    Author:  Syl

  ==============================================================================
*/

#include "GroupChannel.h"

Manifold::Audio::GroupChannel::GroupChannel(int internalId, std::string name) : 
    InternalChannel(internalId, name, CHANNEL_TYPE::GROUP)
{
}

Manifold::Audio::GroupChannel::GroupChannel(const GroupChannel& other) : InternalChannel(static_cast<const InternalChannel&>(other))
{
}
