/*
  ==============================================================================

    ButtonListener.h
    Created: 22 Apr 2022 3:08:00am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ButtonListener.h"

namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            class SVGButton;
            struct ButtonListener
            {
                virtual ~ButtonListener() { }
                virtual void svgButtonClicked(SVGButton* b) = 0;
            };
        }
    }
}