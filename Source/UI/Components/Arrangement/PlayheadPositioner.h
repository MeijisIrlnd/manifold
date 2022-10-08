/*
  ==============================================================================

    PlayheadPositioner.h
    Created: 23 Apr 2022 4:14:31am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <UI/Components/Arrangement/PlayheadCursor.h>
#include "../../../Audio/Core/PositionTracker.h"
namespace Manifold
{
    namespace UI
    {
        class PlayheadPositioner : public juce::Component, public juce::Timer
        {
        public: 
            PlayheadPositioner();
            ~PlayheadPositioner() override;
            void timerCallback() override;
            MANIFOLD_INLINE void shownTimeRangeChanged(const std::pair<double, double>& newTimeRange) {
                m_shownTimeRange = newTimeRange;
            }
            void paint(juce::Graphics& g) override;
            void resized() override;
        private:
            juce::uint64& m_sampleCounter;
            std::pair<double, double> m_shownTimeRange{ 0, 10 };
            PlayheadCursor m_cursor;
        };
    }
}