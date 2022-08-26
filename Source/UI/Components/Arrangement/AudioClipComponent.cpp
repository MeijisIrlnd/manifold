/*
  ==============================================================================

    AudioClipComponent.cpp
    Created: 26 Aug 2022 3:09:51am
    Author:  Syl

  ==============================================================================
*/

#include "AudioClipComponent.h"

namespace Manifold::UI
{
    AudioClipComponent::AudioClipComponent(juce::AudioThumbnailCache& cache, Audio::CachedAudioFile::Ptr cacheItem) : m_cache(cache), m_thumbnail(512, Audio::AudioCache::getInstance()->getFormatManager(), m_cache)
    {
        m_thumbnail.reset(cacheItem->buffer.getNumChannels(), 44100, cacheItem->buffer.getNumSamples());
        m_thumbnail.addBlock(0, cacheItem->buffer, 0, cacheItem->buffer.getNumSamples());

    }

    AudioClipComponent::~AudioClipComponent()
    {
    }

    void AudioClipComponent::paint(juce::Graphics& g)
    {
        g.setColour(juce::Colours::black);
        m_thumbnail.drawChannels(g, getLocalBounds(), 0, m_thumbnail.getTotalLength(), 1);
    }

    void AudioClipComponent::resized()
    {
    }
}