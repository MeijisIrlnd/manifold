/*
  ==============================================================================

    GroupChannelProcessor.cpp
    Created: 11 Jun 2022 3:39:23am
    Author:  Syl

  ==============================================================================
*/

#include "GroupChannelProcessor.h"
namespace Manifold::Audio::Core
{
    GroupChannelProcessor::GroupChannelProcessor(GroupChannel* internalChannel) : 
        BaseChannelProcessor(CHANNEL_TYPE::GROUP, dynamic_cast<InternalChannel*>(internalChannel))
    {
    }

    void GroupChannelProcessor::prepareToPlay(double sampleRate, int samplesPerBlockExpected)
    {
        m_sampleRate = sampleRate;
        m_samplesPerBlock = samplesPerBlockExpected;
    }

    void GroupChannelProcessor::processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
    {
        for (auto& i : m_inserts) {
            if (i != nullptr) {
                i->processBlock(buffer, messages);
            }
        }

        buffer.applyGain(static_cast<float>(GET_PARAM_AS_VALUE(m_associatedChannel, "volume").getValue()));
        if (static_cast<bool>(GET_PARAM_AS_VALUE(m_associatedChannel, "mute").getValue())) {
            buffer.applyGain(0);
        }
        for (auto channel = 0; channel < buffer.getNumChannels(); channel++) {
            float panGain = channel == 0 ? std::sinf(static_cast<float>(m_pan.getValue()) * juce::MathConstants<float>::halfPi) :
                std::cosf(static_cast<float>(m_pan.getValue()) * juce::MathConstants<float>::halfPi);
            buffer.applyGain(channel, 0, buffer.getNumSamples(), panGain);
        }
    }

    void GroupChannelProcessor::releaseResources()
    {
    }
}