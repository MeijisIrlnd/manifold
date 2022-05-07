/*
  ==============================================================================

    ImageButton.h
    Created: 7 May 2022 10:56:12pm
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
            class ImageButton : public BaseButton
            {
            public: 
                void paint(juce::Graphics& g) override;
                void resized() override;

            private: 

            };

            class ImageToggleButton : public BaseToggleButton
            {
            public: 
                ImageToggleButton(const char* offImage, const int offImageSize, 
                    const char* onImage, const int onImageSize);
                void mouseUp(const juce::MouseEvent& ev) override;
                void paint(juce::Graphics& g) override;
                void resized() override;
                
            private: 
                juce::Image m_offImage;
                juce::Image m_onImage;
            };
        }
    }
}