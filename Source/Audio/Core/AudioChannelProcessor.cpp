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
                m_samplesPerBlock = samplesPerBlockExpected;
            }
            void AudioChannelProcessor::processBlock(MANIFOLD_UNUSED juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
            {
                for (auto& i : m_inserts) {
                    if (i != nullptr) {
                        i->processBlock(buffer, messages);
                    }
                }
                
                if (static_cast<bool>(m_mute.getValue())) { buffer.applyGain(0.0f); }
                for (auto channel = 0; channel < buffer.getNumChannels(); channel++) {
                    float panGain = channel == 0 ? std::sinf(static_cast<float>(m_pan.getValue()) * juce::MathConstants<float>::halfPi) :
                        std::cosf(static_cast<float>(m_pan.getValue()) * juce::MathConstants<float>::halfPi);
                    buffer.applyGain(channel, 0, buffer.getNumSamples(), panGain);
                }

            }
            void AudioChannelProcessor::releaseResources()
            {
            }
        }
    }
}