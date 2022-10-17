/*
  ==============================================================================

    AudioLaneData.h
    Created: 8 Oct 2022 2:56:34am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <map>
#include <stdint.h>
#include <Utils/AudioCache.h>
namespace Manifold::Audio
{
    class AudioLaneData
    {
    public:
        struct Clip
        {
            Clip() = default;
            Clip(CachedAudioFile::Ptr _audioFile) : audioFile(_audioFile) {} 
            Clip(CachedAudioFile::Ptr _audioFile, std::uint64_t _lengthInSamples) : audioFile(_audioFile), lengthInSamples(_lengthInSamples) {} 

            CachedAudioFile::Ptr audioFile;
            std::uint64_t lengthInSamples;
        };

        AudioLaneData();
        ~AudioLaneData();
        void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
        void getNextAudioBlock(juce::AudioBuffer<float>& bufferToFill);
        void releaseResources();

        MANIFOLD_INLINE void addSample(double time, const Clip& toAdd) {
            std::uint64_t sample = static_cast<std::uint64_t>(time * m_sampleRate);
            m_laneData[sample] = toAdd;
            m_laneData[sample].lengthInSamples = toAdd.audioFile->buffer.getNumSamples();
        }
        // Todo: remove at index, need some kind of notify if this makes current clip go null as well...

    private: 
        int m_bufferSize{ 0 };
        double m_sampleRate{ 0 };
        std::map<std::uint64_t, Clip> m_laneData;
        Clip* m_currentlyPlayingClip{ nullptr };
        juce::uint64& m_sampleCounter;
        std::uint64_t m_clipSampleIndex{ 0 };

    };
}