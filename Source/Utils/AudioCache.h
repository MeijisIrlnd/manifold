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
        static CachedAudioFile::Ptr addToCache(const juce::File& file);
        static CachedAudioFile::Ptr getFromCache(const juce::File& file);
        bool isAudioFormat(const juce::File& f);
    private:
        void timerCallback() override;
        static std::map<juce::int64, CachedAudioFile::Ptr> m_cache;
        static std::mutex m_mutex;
        static AudioCache* m_instance;
        juce::AudioFormatManager m_formatManager;
    };
}