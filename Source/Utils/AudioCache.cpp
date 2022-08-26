/*
  ==============================================================================

    AudioCache.cpp
    Created: 22 Aug 2022 12:04:50am
    Author:  Syl

  ==============================================================================
*/

#include "AudioCache.h"

namespace Manifold::Audio
{
    std::mutex AudioCache::m_mutex;
    AudioCache* AudioCache::m_instance{ nullptr };
    std::map<juce::int64, CachedAudioFile::Ptr> AudioCache::m_cache;

    CachedAudioFile::Ptr AudioCache::addToCache(const juce::File& f)
    {
        auto* instance = getInstance();
        std::unique_ptr<juce::AudioFormatReader> reader(m_instance->m_formatManager.createReaderFor(f));
        juce::AudioBuffer<float> buffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));
        reader->read(&buffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
        auto hash = f.getFullPathName().hashCode64();
        instance->m_cache[hash] = new CachedAudioFile(f, hash, buffer);
        return instance->m_cache[hash];
    }

    CachedAudioFile::Ptr AudioCache::getFromCache(const juce::File& f)
    {
        auto* instance = getInstance();
        auto hash = f.getFullPathName().hashCode64();
        auto it = instance->m_cache.find(hash);
        if (it == instance->m_cache.end()) return nullptr;
        return instance->m_cache.at(hash);
    }

    void AudioCache::timerCallback()
    {
        std::vector<std::map<juce::int64, CachedAudioFile::Ptr>::iterator> toDelete;
        for (auto it = m_cache.begin(); it != m_cache.end();) {
            std::stringstream dbgMessage;
            dbgMessage << it->second->associatedFile.getFileName() << ", num refs: " << it->second->getReferenceCount() - 1 << "\n";
            DBG(dbgMessage.str());
            if (it->second->getReferenceCount() == 1) {
                // This is the only reference to that file, so delete it..
                it->second = nullptr;
                DBG("Deleting");
                m_cache.erase(it++);
            }
            else {
                ++it;
            }
        }
    }

    AudioCache::AudioCache()
    {
        m_formatManager.registerBasicFormats();
        startTimer(2000);
    }

    AudioCache::~AudioCache()
    {
    }

    void AudioCache::startup()
    {
        getInstance();
    }

    AudioCache* AudioCache::getInstance()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        if (m_instance == nullptr) {
            m_instance = new AudioCache();
        }
        return m_instance;
    }

    void AudioCache::shutdown()
    {
        getInstance()->stopTimer();
        getInstance()->timerCallback();

        delete m_instance;
        m_instance = nullptr;
    }

}
