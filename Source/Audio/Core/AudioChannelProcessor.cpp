/*
  ==============================================================================

    AudioChannelProcessor.cpp
    Created: 8 May 2022 6:30:32pm
    Author:  Syl

  ==============================================================================
*/

#include "AudioChannelProcessor.h"

namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            AudioChannelProcessor::AudioChannelProcessor(AudioChannel* associatedChannel) : 
                BaseChannelProcessor(AUDIO_CHANNEL, dynamic_cast<InternalChannel*>(associatedChannel))
            {
                
            }


            void AudioChannelProcessor::prepareToPlay(double sampleRate, MANIFOLD_UNUSED int samplesPerBlockExpected)
            {
                m_sampleRate = sampleRate;
            }
            void AudioChannelProcessor::processBlock(MANIFOLD_UNUSED juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
            {
            }
            void AudioChannelProcessor::releaseResources()
            {
            }
        }
    }
}