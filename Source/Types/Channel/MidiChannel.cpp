/*
  ==============================================================================

    MidiChannel.cpp
    Created: 8 May 2022 4:10:47am
    Author:  Syl

  ==============================================================================
*/

#include "MidiChannel.h"

namespace Manifold
{
    namespace Audio
    {
        MidiChannel::MidiChannel(int internalId, std::string name) : InternalChannel(internalId, name, CHANNEL_TYPE::MIDI)
        {
        }

        MidiChannel::MidiChannel(const MidiChannel& other) : InternalChannel(static_cast<const InternalChannel&>(other))
        {
        }
    }
}