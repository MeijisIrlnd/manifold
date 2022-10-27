/*
  ==============================================================================

    ChannelLane.h
    Created: 26 Aug 2022 2:15:57am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <map>
#include <JuceHeader.h>
#include <Types/Channel/InternalChannel.h>
#include "AudioClipComponent.h"
namespace Manifold::UI
{
    class ChannelLane : public juce::Component, public juce::FileDragAndDropTarget
    {
    public: 
        ChannelLane(Audio::InternalChannel* internalChannel);
        ~ChannelLane() override;
        bool isInterestedInFileDrag(const juce::StringArray& files) override;
        void filesDropped(const juce::StringArray& files, int x, int y) override;
        void mouseDown(const juce::MouseEvent& ev) override;
        void mouseUp(const juce::MouseEvent& ev) override;
        void childClipMoved(double prevStartTime, double newX);
        void shownTimeRangeChanged(const std::pair<double, double>& shownTimeRange);
        void zoomLevelChanged(const std::pair<double, double>& shownTimeRange);
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        Audio::InternalChannel* m_internalChannel;
        juce::AudioThumbnailCache m_cache;
        // TODO: SYNC this with the timeline component..
        std::pair<double, double> m_currentlyShownTimeRange{ 0, 10 };
        std::map<double, std::unique_ptr<AudioClipComponent> > m_clips;
    };
}