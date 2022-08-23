/*
  ==============================================================================

    TimelineComponent.h
    Created: 23 Aug 2022 1:57:15am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <sstream>
#include <JuceHeader.h>

#include <Audio/Core/PositionTracker.h>
namespace Manifold::UI
{
    /// <summary>
    /// Stream of consciousness: 
    /// What matters here is actually the playhead pos, and your zoom resolution. Zoom should just dictate how long to show (in seconds)
    /// The time sig is obviously going to affect the bar line positioning, as is the bpm.
    /// Before trying a scroll view then, lets just TRY a redraw here instead..
    /// </summary>
    class TimelineComponent : public juce::Component, public juce::ChangeListener
    {
    public: 
        TimelineComponent();
        ~TimelineComponent() override;
        MANIFOLD_INLINE double getTimeAmtToShow() const { return m_timeAmtToShow; }
        MANIFOLD_INLINE void setTimeAmtToShow(double newTimeAmtToShow) {
            m_timeAmtToShow = newTimeAmtToShow;
            repaint();
        }
        void changeListenerCallback(juce::ChangeBroadcaster* broadcaster) override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        double m_timeAmtToShow{ 10 };
    };
}