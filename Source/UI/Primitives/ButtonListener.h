/*
  ==============================================================================

    ButtonListener.h
    Created: 22 Apr 2022 3:08:00am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ButtonListener.h"
#include "../../Macros.h"
namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            class SVGButton;
            class ImageToggleButton;
            class LabelButton;
            struct ButtonListener
            {
                virtual ~ButtonListener() { }
                virtual void svgButtonClicked(MANIFOLD_UNUSED SVGButton* b) {};
                virtual void imageToggleButtonClicked(MANIFOLD_UNUSED ImageToggleButton* b, MANIFOLD_UNUSED bool newState) {};
                virtual void labelButtonClicked(MANIFOLD_UNUSED LabelButton* b) {};
            };
        }
    }
}