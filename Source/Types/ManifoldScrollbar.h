/*
  ==============================================================================

    ManifoldScrollbar.h
    Created: 25 Apr 2022 12:35:25am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Manifold
{
    namespace UI
    {
        class ManifoldScrollbar : public juce::ScrollBar
        {
        public: 
            ManifoldScrollbar(bool vertical) : juce::ScrollBar(vertical) { }
            void mouseWheelMove(const juce::MouseEvent& ev, const juce::MouseWheelDetails& d) override { DBG("CALL"); }
        };
    }
}