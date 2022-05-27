/*
  ==============================================================================

    LabelButton.h
    Created: 17 May 2022 12:42:13am
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
            class LabelButton : public BaseButton
            {
            public: 
                LabelButton(const std::string& text);
                void mouseUp(const juce::MouseEvent& ev) override;
                void paint(juce::Graphics& g) override;
                void resized() override;
            private: 
                juce::Label m_label;
            };

        }
    }
}