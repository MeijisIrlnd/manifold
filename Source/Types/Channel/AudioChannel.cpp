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
            std::string groupId = std::to_string(m_internalId);
            m_valueTree.setProperty({ groupId + "_inputmonitor" }, false, nullptr);
            m_valueTree.setProperty({ groupId + "_recordenable" }, false, nullptr);

        }

        AudioChannel::AudioChannel(const AudioChannel& other) : InternalChannel(static_cast<const InternalChannel&>(other))
        {

        }
    }
}

