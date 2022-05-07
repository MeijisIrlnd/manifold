/*
  ==============================================================================

    ColourPickerPopup.h
    Created: 8 May 2022 12:17:47am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Manifold
{
    namespace UI
    {
        class ColourPickerMenuItem : public juce::PopupMenu::CustomComponent
        {
        public: 
            ColourPickerMenuItem(const juce::Colour& colour);
            void getIdealSize(int& idealWidth, int& idealHeight) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            const juce::Colour m_colour;
        };
    }
}