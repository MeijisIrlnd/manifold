/*
  ==============================================================================

    AudioDriver.cpp
    Created: 23 Apr 2022 3:05:08am
    Author:  Syl

  ==============================================================================
*/

#include "AudioDriver.h"
#include <Utils/AudioCache.h>
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            AudioDriver::AudioDriver()
            {
            }

            AudioDriver::~AudioDriver()
            {
            }

            void AudioDriver::prepareToPlay(double sampleRate, MANIFOLD_UNUSED int samplesPerBlock)
            {
                AudioCache::getInstance()->setup(sampleRate);
                GET_POSITION_TRACKER()->prepare(sampleRate);
            }

            void AudioDriver::processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
            {
                if (GET_POSITION_TRACKER()->getIsRunning()) {
                    GET_POSITION_TRACKER()->operator+=(buffer.getNumSamples());
                }
            }

            void AudioDriver::releaseResources()
            {
            }
        }
    }
}

