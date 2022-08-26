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
    AudioClipComponent::AudioClipComponent(Audio::InternalChannel* internalChannel, juce::AudioThumbnailCache& cache, Audio::CachedAudioFile::Ptr cacheItem) : 
        m_associatedChannel(internalChannel), m_cache(cache), m_thumbnail(512, Audio::AudioCache::getInstance()->getFormatManager(), m_cache)
    {
        m_thumbnail.reset(cacheItem->buffer.getNumChannels(), cacheItem->originalSampleRate, cacheItem->buffer.getNumSamples());
        m_thumbnail.addBlock(0, cacheItem->buffer, 0, cacheItem->buffer.getNumSamples());

    }

    AudioClipComponent::~AudioClipComponent()
    {
    }

    void AudioClipComponent::paint(juce::Graphics& g)
    {
        g.setColour(m_associatedChannel->getColour());
        g.drawRect(getLocalBounds(), 1);
        g.setColour(m_associatedChannel->getColour());
        m_thumbnail.drawChannels(g, getLocalBounds(), 0, m_thumbnail.getTotalLength(), 1);
    }

    void AudioClipComponent::resized()
    {
    }
}