/*
  ==============================================================================

    AudioClipComponent.h
    Created: 26 Aug 2022 3:09:51am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Utils/AudioCache.h>
namespace Manifold::UI
{
    class AudioClipComponent : public juce::Component
    {
    public: 
        AudioClipComponent(juce::AudioThumbnailCache& cache, Audio::CachedAudioFile::Ptr cacheItem);
        ~AudioClipComponent() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::AudioThumbnailCache& m_cache;
        juce::AudioThumbnail m_thumbnail;

    };
}