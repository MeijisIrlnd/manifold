/*
  ==============================================================================

    MidiChannel.h
    Created: 8 May 2022 4:10:47am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "InternalChannel.h"

namespace Manifold
{
    namespace Audio
    {
        class MidiChannel : public InternalChannel
        {
        public: 
            MidiChannel(int internalId, std::string name);
            MidiChannel(const MidiChannel& other);
        private: 

        };
    }
}