/*
  ==============================================================================

    OverallLF.h
    Created: 9 May 2022 4:17:10am
    Author:  Syl

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../../Macros.h"
namespace Manifold
{
    namespace UI
    {
        class OverallLF : public juce::LookAndFeel_V4
        {
        public: 
            OverallLF();
            void drawScrollbar(juce::Graphics&, juce::ScrollBar&, int x, int y, int width, int height, bool isScrollbarVertical,
                int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;
        private: 
            juce::Image m_scrollbarThumb;
        };
    }
}