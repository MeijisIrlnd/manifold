/*
  ==============================================================================

    ChannelLane.cpp
    Created: 26 Aug 2022 2:15:57am
    Author:  Syl

  ==============================================================================
*/

#include "ChannelLane.h"
#include <Utils/AudioCache.h>
#include <Types/Channel/AudioChannel.h>
namespace Manifold::UI
{
    ChannelLane::ChannelLane(Audio::InternalChannel* internalChannel) : m_internalChannel(internalChannel), m_cache(5)
    {
        //setInterceptsMouseClicks(false, true);
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

    void ChannelLane::filesDropped(const juce::StringArray& files, int x, MANIFOLD_UNUSED int y)
    {
        Audio::CachedAudioFile::Ptr cachedFile = Audio::AudioCache::addToCache(files[0]);
        auto normalised = x / static_cast<double>(getWidth());
        auto sampleStartTime = m_currentlyShownTimeRange.first + (normalised * (m_currentlyShownTimeRange.second - m_currentlyShownTimeRange.first));
        std::unique_ptr<AudioClipComponent> currentClip(new AudioClipComponent(m_internalChannel, m_cache, cachedFile, sampleStartTime));
        m_clips[sampleStartTime] = std::move(currentClip);
        dynamic_cast<Audio::AudioChannel*>(m_internalChannel)->getLaneData()->addSample(sampleStartTime, Audio::AudioLaneData::Clip(cachedFile));
        addAndMakeVisible(m_clips[sampleStartTime].get());
        resized();
    }


    void ChannelLane::mouseDown(const juce::MouseEvent& ev)
    {
        getParentComponent()->mouseDown(ev.getEventRelativeTo(getParentComponent()));
    }

    void ChannelLane::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
    {
        getParentComponent()->mouseUp(ev.getEventRelativeTo(getParentComponent()));
    }

    void ChannelLane::childClipMoved(double prevStartTime, double newX)
    {
        auto newStartTime = newX / static_cast<double>(getWidth());
        newStartTime = m_currentlyShownTimeRange.first + (newStartTime * (m_currentlyShownTimeRange.second - m_currentlyShownTimeRange.first));
        m_clips[newStartTime].reset(m_clips[prevStartTime].release());
        m_clips.erase(prevStartTime);
        m_clips[newStartTime]->setStartTime(newStartTime);
        resized();
    }

    void ChannelLane::shownTimeRangeChanged(const std::pair<double, double>& shownTimeRange)
    {
        m_currentlyShownTimeRange = shownTimeRange;
        // Recalculate what to show on the screen (which clips etc)
        for (auto it = m_clips.begin(); it != m_clips.end(); it++) {
            MANIFOLD_UNUSED auto len = it->second->getAudioFile()->buffer.getNumSamples() / it->second->getAudioFile()->originalSampleRate;
            if (it->first >= shownTimeRange.first) {
                // Okay fine, so where on the screen does it go? 
                auto startX = (it->first - shownTimeRange.first) / shownTimeRange.second - shownTimeRange.first;
                startX *= getWidth();
                auto sampleEndTime = it->first + (it->second->getAudioFile()->buffer.getNumSamples() / it->second->getAudioFile()->originalSampleRate);
                auto endX = getWidth() * ((sampleEndTime - m_currentlyShownTimeRange.first) / (m_currentlyShownTimeRange.second - m_currentlyShownTimeRange.first));
                auto componentWidth = endX - startX;
                it->second->setVisible(true);
                auto originalBounds = it->second->getBounds();
                it->second->setBounds(static_cast<int>(startX), originalBounds.getY(), static_cast<int>(componentWidth), originalBounds.getHeight());
            }
            else {
                it->second->setVisible(false);
            }
        }
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
            auto startX = getWidth() * ((it->first - m_currentlyShownTimeRange.first) / m_currentlyShownTimeRange.second - m_currentlyShownTimeRange.first);
            auto sampleEndTime = it->first + (it->second->getAudioFile()->buffer.getNumSamples() / it->second->getAudioFile()->originalSampleRate);
            auto endX = getWidth() * ((sampleEndTime - m_currentlyShownTimeRange.first) / (m_currentlyShownTimeRange.second - m_currentlyShownTimeRange.first));
            auto componentWidth = endX - startX;
            it->second->setBounds(static_cast<int>(startX), 0, static_cast<int>(componentWidth), getHeight());
        }
    }

    
}