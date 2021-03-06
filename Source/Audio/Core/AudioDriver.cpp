/*
  ==============================================================================

    AudioDriver.cpp
    Created: 23 Apr 2022 3:05:08am
    Author:  Syl

  ==============================================================================
*/

#include "AudioDriver.h"

namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            AudioDriver::AudioDriver(PositionTracker& positionTracker) :
                m_positionTracker(positionTracker)
            {
            }

            AudioDriver::~AudioDriver()
            {
            }

            void AudioDriver::prepareToPlay(double sampleRate, MANIFOLD_UNUSED int samplesPerBlock)
            {
                m_positionTracker.prepare(sampleRate);
            }

            void AudioDriver::processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
            {
                if (m_positionTracker.getIsRunning()) {
                    m_positionTracker += buffer.getNumSamples();
                }
            }

            void AudioDriver::releaseResources()
            {
            }
        }
    }
}

