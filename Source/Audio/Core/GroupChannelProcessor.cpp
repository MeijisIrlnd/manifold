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
    GroupChannelProcessor::GroupChannelProcessor(InternalChannel* internalChannel) : 
        BaseChannelProcessor(CHANNEL_TYPE::GROUP, internalChannel)
    {
    }

    void GroupChannelProcessor::prepareToPlay(MANIFOLD_UNUSED double sampleRate, MANIFOLD_UNUSED int samplesPerBlockExpected)
    {
    }

    void GroupChannelProcessor::processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages)
    {
        buffer.applyGain(static_cast<float>(GET_PARAM_AS_VALUE(m_associatedChannel, "volume").getValue()));
        if (static_cast<bool>(GET_PARAM_AS_VALUE(m_associatedChannel, "mute").getValue())) {
            buffer.applyGain(0);
        }
    }

    void GroupChannelProcessor::releaseResources()
    {
    }
}