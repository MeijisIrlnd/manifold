/*
  ==============================================================================

    AudioClipComponent.cpp
    Created: 26 Aug 2022 3:09:51am
    Author:  Syl

  ==============================================================================
*/

#include "AudioClipComponent.h"
#include "ChannelLane.h"

namespace Manifold::UI
{
    AudioClipComponent::AudioClipComponent(Audio::InternalChannel* internalChannel, juce::AudioThumbnailCache& cache, Audio::CachedAudioFile::Ptr cacheItem, const double startTime) : 
        m_associatedChannel(internalChannel), m_cache(cache), m_thumbnail(512, Audio::AudioCache::getInstance()->getFormatManager(), m_cache), m_cachedFile(cacheItem), m_startTime(startTime)
    {
        m_thumbnail.reset(cacheItem->buffer.getNumChannels(), cacheItem->originalSampleRate, cacheItem->buffer.getNumSamples());
        m_thumbnail.addBlock(0, cacheItem->buffer, 0, cacheItem->buffer.getNumSamples());

    }

    AudioClipComponent::~AudioClipComponent()
    {
    }

    void AudioClipComponent::mouseDown(const juce::MouseEvent& ev)
    {
        m_xAtDragStart = static_cast<double>(getBoundsInParent().getX());
        m_dragger.startDraggingComponent(this, ev);
    }

    void AudioClipComponent::mouseDrag(const juce::MouseEvent& ev)
    {
        m_dragger.dragComponent(this, ev, &m_constrainer);
    }

    void AudioClipComponent::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
    {
        if (static_cast<double>(getBoundsInParent().getX()) != m_xAtDragStart) {
            dynamic_cast<ChannelLane*>(getParentComponent())->childClipMoved(m_startTime, static_cast<double>(getBoundsInParent().getX()));
        }
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
        m_constrainer.setMinimumOnscreenAmounts(getHeight(), 0, getHeight(), 0);
    }
}