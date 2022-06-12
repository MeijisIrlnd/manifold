/*
  ==============================================================================

    GroupMixerChannel.cpp
    Created: 12 Jun 2022 6:53:22pm
    Author:  Syl

  ==============================================================================
*/

#include "GroupMixerChannel.h"

namespace Manifold::UI
{
    GroupMixerChannel::GroupMixerChannel(Manifold::Audio::InternalChannel* associatedChannel) : 
        MixerChannel(associatedChannel)
    {

    }
    
    void GroupMixerChannel::resized()
    {
        drawCommonElements();

    }
}