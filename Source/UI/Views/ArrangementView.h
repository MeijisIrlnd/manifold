/*
  ==============================================================================

    ArrangementView.h
    Created: 24 Apr 2022 10:21:47pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <algorithm>
#include <JuceHeader.h>
#include "../../Audio/ManifoldEngine.h"
#include "../Components/Arrangement/ChannelListComponent.h"
#include "../../Audio/ManifoldEngine.h"
#include "PlaylistView.h"
#include "../../Types/ManifoldScrollbar.h"
#include <UI/Components/Arrangement/TimelineComponent.h>
#include <UI/Components/SampleBrowser/SampleBrowserComponent.h>
#include <UI/Components/Arrangement/PlayheadPositioner.h>
namespace Manifold
{
    namespace UI
    {
        class ArrangementView : public juce::Component, public ViewListener,
            public juce::ScrollBar::Listener
        {
        public: 
            ArrangementView();
            ~ArrangementView() override;
            void mouseWheelMove(const juce::MouseEvent& ev, const juce::MouseWheelDetails& wheel) override;
            void playlistViewScroll(double newValue) override;
            void scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart) override;
            void paint(juce::Graphics& g) override;
            void resized() override;

        private: 
            juce::Viewport m_channelListViewport;
            ChannelListComponent m_channelListComponent;
            juce::Viewport m_playlistViewport;
            PlaylistView m_playlistView;
            ManifoldScrollbar m_horizontalScrollbar;
            ManifoldScrollbar m_verticalScrollbar;
            TimelineComponent m_timelineComponent;
            PlayheadPositioner m_playheadPositioner;
            //SampleBrowserComponent m_sampleBrowserComponent;
            double m_zoom = 10;
        };
    }
}