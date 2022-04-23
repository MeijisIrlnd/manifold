/*
  ==============================================================================

    BaseButton.h
    Created: 22 Apr 2022 2:18:29am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ButtonListener.h"
namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            class BaseButton : public juce::Component 
            {
            public: 
                BaseButton() = default;
                ~BaseButton() override { }
                void addListener(ButtonListener* l) { m_listener = l; }
                virtual void paint(juce::Graphics& g) override = 0;
                virtual void resized() override = 0;
            protected: 
                ButtonListener* m_listener;

            };
        }
    }
}