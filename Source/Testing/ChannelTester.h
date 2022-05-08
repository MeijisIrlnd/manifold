/*
  ==============================================================================

    ChannelTester.h
    Created: 7 May 2022 7:05:56pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "../Macros.h"
#include "../Audio/ManifoldEngine.h"
namespace Manifold
{
    namespace Testing
    {
        class ChannelTester
        {
        public: 
            ChannelTester()
            {
                for (auto i = 0; i < 4; i++) {
                    GET_ENGINE->createChannel(AUDIO_CHANNEL);
                }
                for (auto i = 0; i < 4; i++) {
                    GET_ENGINE->createChannel(MIDI_CHANNEL);
                }
            }
        private: 

        };
    }
}