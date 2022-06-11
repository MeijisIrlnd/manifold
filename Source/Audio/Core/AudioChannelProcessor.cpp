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
                m_volume = GET_PARAM_AS_VALUE(associatedChannel, "volume");
                m_pan = GET_PARAM_AS_VALUE(associatedChannel, "pan");
                m_mute = GET_PARAM_AS_VALUE(associatedChannel, "mute");
                m_solo = GET_PARAM_AS_VALUE(associatedChannel, "solo");
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
                
                buffer.applyGain(static_cast<float>(m_volume.getValue()));
                if (static_cast<bool>(m_mute.getValue())) { buffer.applyGain(0.0f); }

            }
            void AudioChannelProcessor::releaseResources()
            {
            }
        }
    }
}