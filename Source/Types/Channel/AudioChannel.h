/*
  ==============================================================================

    AudioChannel.h
    Created: 8 May 2022 4:10:40am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "InternalChannel.h"
namespace Manifold
{
    namespace Audio
    {
        class AudioChannel : public InternalChannel
        {
        public: 
            AudioChannel(int internalId, std::string name);
            AudioChannel(const AudioChannel& other);
        private: 
            // Also holds audio data, etc
        };
    }
}