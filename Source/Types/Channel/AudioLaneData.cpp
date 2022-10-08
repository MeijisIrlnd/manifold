/*
  ==============================================================================

    AudioLaneData.cpp
    Created: 8 Oct 2022 2:56:34am
    Author:  Syl

  ==============================================================================
*/

#include "AudioLaneData.h"
#include <Audio/Core/PositionTracker.h>
namespace Manifold::Audio
{
    AudioLaneData::AudioLaneData() : m_sampleCounter(GET_POSITION_TRACKER()->m_sampleCounter)
    {
    }

    AudioLaneData::~AudioLaneData()
    {
    }

    MANIFOLD_UNUSED void AudioLaneData::prepareToPlay(MANIFOLD_UNUSED int samplesPerBlockExpected, MANIFOLD_UNUSED double sampleRate)
    {
    }

    MANIFOLD_UNUSED void AudioLaneData::getNextAudioBlock(MANIFOLD_UNUSED juce::AudioBuffer<float>& bufferToFill)
    {
    }

    MANIFOLD_UNUSED void AudioLaneData::releaseResources()
    {
    }
}