/*
  ==============================================================================

    PlaylistView.h
    Created: 23 Apr 2022 4:08:25pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Components/PlayheadPositioner.h"
#include "../ViewListener.h"
#include <algorithm>
namespace Manifold
{
    namespace UI
    {
        class PlaylistView : public juce::Component
        {
        public: 
            PlaylistView(Manifold::Audio::Core::PositionTracker* positionTracker);
            ~PlaylistView() override;
            MANIFOLD_INLINE void addListener(ViewListener* newListener) { m_listener = newListener; }
            void mouseWheelMove(const juce::MouseEvent& ev, const juce::MouseWheelDetails& wheel) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            ViewListener* m_listener = nullptr;
            PlayheadPositioner m_playheadPositioner;
            double currentMouseWheel = 0;

            // so at 0 zoom, timescale should show 15 seconds..

        };
    }
}