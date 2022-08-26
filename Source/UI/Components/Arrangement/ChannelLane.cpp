/*
  ==============================================================================

    ChannelLane.cpp
    Created: 26 Aug 2022 2:15:57am
    Author:  Syl

  ==============================================================================
*/

#include "ChannelLane.h"
#include <Utils/AudioCache.h>
namespace Manifold::UI
{
    ChannelLane::ChannelLane(Audio::InternalChannel* internalChannel) : m_internalChannel(internalChannel), m_cache(5)
    {
    }

    ChannelLane::~ChannelLane()
    {

    }

    bool ChannelLane::isInterestedInFileDrag(MANIFOLD_UNUSED const juce::StringArray& files)
    {

        // Only care if the file is an audio file (Obviously needs to work with multiple files maybe...
        auto f = files[0];
        return Audio::AudioCache::getInstance()->isAudioFormat(f);
    }

    void ChannelLane::filesDropped(const juce::StringArray& files, MANIFOLD_UNUSED int x, MANIFOLD_UNUSED int y)
    {
        Audio::CachedAudioFile::Ptr cachedFile = Audio::AudioCache::addToCache(files[0]);
        // Need to know what width to draw this, that's gonna be based on the time scale...
        // SO could you say the width is proportional to the currently rendered region? 
        
        std::unique_ptr<AudioClipComponent> currentClip(new AudioClipComponent(m_cache, cachedFile));
        m_clips[x] = std::move(currentClip);
        addAndMakeVisible(m_clips[x].get());
        resized();
    }


    void ChannelLane::paint(juce::Graphics& g)
    {
        g.fillAll(m_internalChannel->getColour().withAlpha(0.2f));
        g.setColour(juce::Colour(0x7FFFFFFF));
        juce::Line<float> endBorder(0, static_cast<float>(getHeight()), static_cast<float>(getWidth()), static_cast<float>(getHeight()));
        g.drawLine(endBorder, 5.0f);
    }

    void ChannelLane::resized()
    {
        for (auto it = m_clips.begin(); it != m_clips.end(); it++) {
            it->second->setBounds(it->first, 0, getWidth() / 4, getHeight());
        }
    }
}