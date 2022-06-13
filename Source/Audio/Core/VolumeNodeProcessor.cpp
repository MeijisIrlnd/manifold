/*
  ==============================================================================

    VolumeNodeProcessor.cpp
    Created: 12 Jun 2022 10:59:56pm
    Author:  Syl

  ==============================================================================
*/

#include "VolumeNodeProcessor.h"

namespace Manifold::Audio::Core
{
    VolumeNodeProcessor::VolumeNodeProcessor(InternalChannel* associatedChannel) : 
        m_associatedChannel(associatedChannel)
    {
        m_volume = GET_PARAM_AS_VALUE(associatedChannel, "volume");
    }

    void VolumeNodeProcessor::prepareToPlay(MANIFOLD_UNUSED double sampleRate, MANIFOLD_UNUSED int samplesPerBlockExpected)
    {
    }

    void VolumeNodeProcessor::processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& midiBuffer)
    {
        buffer.applyGain(static_cast<float>(m_volume.getValue()));
    }

    void VolumeNodeProcessor::releaseResources()
    {
    }
}