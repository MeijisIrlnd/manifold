/*
  ==============================================================================

    PlayheadPositioner.h
    Created: 23 Apr 2022 4:14:31am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Audio/Core/PositionTracker.h"
namespace Manifold
{
    namespace UI
    {
        class PlayheadPositioner : public juce::Component, public juce::ChangeListener
        {
        public: 
            PlayheadPositioner();
            ~PlayheadPositioner() override;
            void changeListenerCallback(juce::ChangeBroadcaster* source) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private:
        };
    }
}