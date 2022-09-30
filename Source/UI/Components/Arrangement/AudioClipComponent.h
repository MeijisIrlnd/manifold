/*
  ==============================================================================

    AudioClipComponent.h
    Created: 26 Aug 2022 3:09:51am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Types/Channel/InternalChannel.h>
#include <Utils/AudioCache.h>
namespace Manifold::UI
{
    class AudioClipComponent : public juce::Component
    {
    public: 
        AudioClipComponent(Audio::InternalChannel* associatedChannel, juce::AudioThumbnailCache& cache, Audio::CachedAudioFile::Ptr cacheItem, const double startTime);
        ~AudioClipComponent() override;
        MANIFOLD_INLINE Audio::CachedAudioFile::Ptr getAudioFile() { return m_cachedFile; }
        MANIFOLD_INLINE void setStartTime(double newStartTime) { m_startTime = newStartTime; }
        void mouseDown(const juce::MouseEvent& ev) override;
        void mouseDrag(const juce::MouseEvent& ev) override;
        void mouseUp(const juce::MouseEvent& ev) override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        double m_startTime{ 0 };
        double m_xAtDragStart{ 0 };
        Audio::InternalChannel* m_associatedChannel;
        Audio::CachedAudioFile::Ptr m_cachedFile{nullptr};
        juce::AudioThumbnailCache& m_cache;
        juce::AudioThumbnail m_thumbnail;
        juce::ComponentDragger m_dragger;
        juce::ComponentBoundsConstrainer m_constrainer;

    };
}