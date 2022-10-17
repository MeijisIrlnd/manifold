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

    MANIFOLD_UNUSED void AudioLaneData::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
    {
        m_bufferSize = samplesPerBlockExpected;
        m_sampleRate = sampleRate;
    }

    MANIFOLD_UNUSED void AudioLaneData::getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill)
    {
        if (GET_POSITION_TRACKER()->getIsRunning()) 
        {
            // can use sample counter to narrow the search range probably
            auto write = bufferToFill.getArrayOfWritePointers();
            for (auto sample = 0; sample < bufferToFill.getNumSamples(); sample++)
            {
                if (m_laneData.find(static_cast<std::uint64_t>(m_sampleCounter + sample)) != m_laneData.end()) {
                    // Guaranteed to have started a sample here (KISS for now) 
                    m_currentlyPlayingClip = &m_laneData[m_sampleCounter + sample];
                    m_clipSampleIndex = 0;
                }
                if (m_currentlyPlayingClip != nullptr) {
                    std::scoped_lock<std::mutex> sl(m_currentlyPlayingClip->audioFile->mutex);
                    if (m_clipSampleIndex < m_currentlyPlayingClip->lengthInSamples)
                    {
                        auto* read = m_currentlyPlayingClip->audioFile->buffer.getArrayOfReadPointers();
                        for (auto channel = 0; channel < m_currentlyPlayingClip->audioFile->buffer.getNumChannels(); channel++) {
                            write[channel][sample] += read[channel][m_clipSampleIndex];
                        }
                        ++m_clipSampleIndex;
                    }
                }
            }
        }
    }

    MANIFOLD_UNUSED void AudioLaneData::releaseResources()
    {
        m_currentlyPlayingClip = nullptr;
    }
}