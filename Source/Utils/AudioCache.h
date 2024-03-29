/*
  ==============================================================================

    AudioCache.h
    Created: 22 Aug 2022 12:04:50am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <mutex>
#include <map>
#include <JuceHeader.h>
#include "CachedAudioFile.h"
#include <Macros.h>
namespace Manifold::Audio
{
    class AudioCache : public juce::Timer
    {
    protected: 
        AudioCache();
    public:
        ~AudioCache();
        AudioCache(const AudioCache& other) = delete;
        AudioCache(AudioCache&& other) = delete;
        static void startup();
        static AudioCache* getInstance();
        static void shutdown();
        static juce::AudioBuffer<float> resampleBuffer(juce::AudioBuffer<float>& toResample, double originalSampleRate, double newSampleRate);
        static CachedAudioFile::Ptr addToCache(const juce::File& file);
        static CachedAudioFile::Ptr getFromCache(const juce::File& file);
        MANIFOLD_INLINE void setup(double sampleRate) { m_sampleRate = sampleRate; }
        bool isAudioFormat(const juce::File& f);
        MANIFOLD_INLINE juce::AudioFormatManager& getFormatManager() { return m_formatManager; }
    private:
        void timerCallback() override;
        double m_sampleRate{ 0 };
        static std::map<juce::int64, CachedAudioFile::Ptr> m_cache;
        static std::mutex m_mutex;
        static AudioCache* m_instance;
        juce::AudioFormatManager m_formatManager;
    };
}