/*
  ==============================================================================

    AudioChannel.cpp
    Created: 8 May 2022 4:10:40am
    Author:  Syl

  ==============================================================================
*/

#include "AudioChannel.h"

namespace Manifold
{
    namespace Audio
    {
        AudioChannel::AudioChannel(int internalId, std::string name) : InternalChannel(internalId, name, CHANNEL_TYPE::AUDIO)
        {
        }

        AudioChannel::AudioChannel(const AudioChannel& other) : InternalChannel(static_cast<const InternalChannel&>(other))
        {
        }
    }
}

