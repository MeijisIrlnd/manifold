/*
  ==============================================================================

    TimestripComponent.h
    Created: 23 Apr 2022 4:34:12pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Manifold
{
    namespace UI
    {
        class TimestripComponent : public juce::Component
        {
        public: 
            TimestripComponent();
            ~TimestripComponent() override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            
        };
    }
}