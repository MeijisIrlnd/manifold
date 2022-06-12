/*
  ==============================================================================

    GroupMixerChannel.h
    Created: 12 Jun 2022 6:53:22pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "MixerChannel.h"
namespace Manifold::UI
{
    class GroupMixerChannel : public MixerChannel
    {
    public: 
        GroupMixerChannel(Manifold::Audio::InternalChannel* associatedChannel);
        void resized() override;
    private: 

    };
}