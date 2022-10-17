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
        auto hash = f.getFullPathName().hashCode64();
        auto* instance = getInstance();
        auto it = instance->m_cache.find(hash);
        if (it == instance->m_cache.end()) {
            std::unique_ptr<juce::AudioFormatReader> reader(m_instance->m_formatManager.createReaderFor(f));
            juce::AudioBuffer<float> inBuffer(reader->numChannels, static_cast<int>(reader->lengthInSamples));
            // Resample.... 
            jassert(getInstance()->m_sampleRate != 0);
            reader->read(&inBuffer, 0, static_cast<int>(reader->lengthInSamples), 0, true, true);
            juce::AudioBuffer<float> buffer = resampleBuffer(inBuffer, reader->sampleRate, getInstance()->m_sampleRate);
            instance->m_cache[hash] = new CachedAudioFile(f, hash, buffer, getInstance()->m_sampleRate);
            return instance->m_cache[hash];
        }
        else {
            return getFromCache(f);
        }
    }

    CachedAudioFile::Ptr AudioCache::getFromCache(const juce::File& f)
    {
        auto* instance = getInstance();
        auto hash = f.getFullPathName().hashCode64();
        auto it = instance->m_cache.find(hash);
        if (it == instance->m_cache.end()) return nullptr;
        return instance->m_cache.at(hash);
    }

    bool AudioCache::isAudioFormat(const juce::File& f)
    {
        auto* fmt = m_formatManager.findFormatForFileExtension(f.getFileExtension());
        return fmt != nullptr;
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
                DBG("No more refs, removing from cache");
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

    juce::AudioBuffer<float> AudioCache::resampleBuffer(juce::AudioBuffer<float>& toResample, double originalSampleRate, double newSampleRate)
    {
        juce::AudioBuffer<float> resampled;
        double ratio = originalSampleRate / newSampleRate;
        resampled.setSize(toResample.getNumChannels(), static_cast<int>(toResample.getNumSamples() / ratio));
        auto* read = toResample.getArrayOfReadPointers();
        auto* write = resampled.getArrayOfWritePointers();
        for (auto channel = 0; channel < toResample.getNumChannels(); channel++) {
            juce::LagrangeInterpolator resampler;       
            resampler.reset();
            resampler.process(ratio, read[channel], write[channel], resampled.getNumSamples());
        }
        return resampled;
    }

}
