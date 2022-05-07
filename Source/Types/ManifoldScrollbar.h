/*
  ==============================================================================

    ManifoldScrollbar.h
    Created: 25 Apr 2022 12:35:25am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
namespace Manifold
{
    namespace UI
    {
        class ManifoldScrollbar : public juce::ScrollBar
        {
        public: 
            ManifoldScrollbar(bool vertical) : juce::ScrollBar(vertical) { }
            void mouseWheelMove(MANIFOLD_UNUSED const juce::MouseEvent& ev, MANIFOLD_UNUSED const juce::MouseWheelDetails& d) override { DBG("CALL"); }
        };
    }
}