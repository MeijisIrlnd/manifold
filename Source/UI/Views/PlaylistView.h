/*
  ==============================================================================

    PlaylistView.h
    Created: 23 Apr 2022 4:08:25pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <algorithm>
#include <vector>
#include <JuceHeader.h>
#include <Audio/ManifoldEngine.h>
#include <UI/Components/Arrangement/ChannelLane.h>
#include "../Components/Arrangement/PlayheadPositioner.h"
#include <UI/Components/Arrangement/ToolMenuItem.h>
#include "../ViewListener.h"
namespace Manifold
{
    namespace UI
    {
        class PlaylistView : public juce::Component, public Audio::EngineListener
        {
        public: 
            PlaylistView();
            ~PlaylistView() override;
            MANIFOLD_INLINE void addListener(ViewListener* newListener) { m_listener = newListener; }
            void shownTimeRangeChanged(const std::pair<double, double>& shownTimeRange);
            void onChannelCreated(MANIFOLD_UNUSED Audio::InternalChannel* newChannel) override;
            void onChannelDeleted(MANIFOLD_UNUSED Audio::InternalChannel* toDelete) override;
            void mouseWheelMove(const juce::MouseEvent& ev, const juce::MouseWheelDetails& wheel) override;
            void mouseDown(const juce::MouseEvent& ev) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            ViewListener* m_listener = nullptr;
            PlayheadPositioner m_playheadPositioner;
            double currentMouseWheel = 0;
            std::vector<std::unique_ptr<ChannelLane> > m_channelLanes;
            // so at 0 zoom, timescale should show 15 seconds..
            juce::PopupMenu m_toolMenu;
            std::vector<std::pair<const void*, int> > m_cursors;

        };
    }
}