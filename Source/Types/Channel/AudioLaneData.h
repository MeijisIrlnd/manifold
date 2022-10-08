/*
  ==============================================================================

    AudioLaneData.h
    Created: 8 Oct 2022 2:56:34am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <map>
#include <Utils/AudioCache.h>
namespace Manifold::Audio
{
    class AudioLaneData
    {
    public:
        struct Clip
        {
            CachedAudioFile::Ptr audioFile;
            float sampleStartTime, sampleEndTime;
        };

        AudioLaneData();
        ~AudioLaneData();
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill);
        void releaseResources();

        MANIFOLD_INLINE void addSample(float time, const Clip& toAdd) {
            m_laneData[time] = toAdd;
        }

    private: 
        std::map<float, Clip> m_laneData;
        Clip* m_currentlyPlayingClip{ nullptr };
        juce::uint64& m_sampleCounter;

    };
}