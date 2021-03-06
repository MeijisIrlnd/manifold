/*
  ==============================================================================

    MidiChannelProcessor.cpp
    Created: 9 May 2022 2:39:29am
    Author:  Syl

  ==============================================================================
*/

#include "MidiChannelProcessor.h"

namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            MidiChannelProcessor::MidiChannelProcessor(InternalChannel* associatedChannel) :
                BaseChannelProcessor(MIDI_CHANNEL, associatedChannel)
            {
                m_pan = GET_PARAM_AS_VALUE(associatedChannel, "pan");
                m_mute = GET_PARAM_AS_VALUE(associatedChannel, "mute");
                m_solo = GET_PARAM_AS_VALUE(associatedChannel, "solo");
            }

            void MidiChannelProcessor::prepareToPlay(double sampleRate, int samplesPerBlockExpected)
            {
                m_sampleRate = sampleRate;
                m_samplesPerBlock = samplesPerBlockExpected;
            }

            void MidiChannelProcessor::processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
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

            void MidiChannelProcessor::releaseResources()
            {
            }
        }
    }
}