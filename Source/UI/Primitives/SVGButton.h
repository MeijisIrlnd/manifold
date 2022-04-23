/*
  ==============================================================================

    SVGButton.h
    Created: 22 Apr 2022 2:24:24am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "BaseButton.h"
namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            class SVGButton : public BaseButton
            {
            public: 
                SVGButton(const void* imageData, int size);
                ~SVGButton();
                const int getClickCount() const;
                void mouseUp(const juce::MouseEvent& ev);
                void paint(juce::Graphics& g) override;
                void resized() override;
            private: 
                std::unique_ptr<juce::Drawable> m_icon;
                int m_clickCount = 0;
            };
        }
    }
}