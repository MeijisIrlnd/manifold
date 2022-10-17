/*
  ==============================================================================

    ArrangementLF.h
    Created: 17 Oct 2022 3:45:16am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Macros.h>
namespace Manifold::UI
{
    class ArrangementLF : public juce::LookAndFeel_V4
    {
    public: 
        ArrangementLF();
        MANIFOLD_INLINE juce::Font getOverallFont() { return m_labelFont; }
        MANIFOLD_INLINE juce::Font getLabelFont(MANIFOLD_UNUSED juce::Label& l) override {
            return m_labelFont.withHeight(18.0f);
        }

        MANIFOLD_INLINE juce::Font getPopupMenuFont() override
        {
            return m_labelFont.withHeight(12.0f);
        }
    private: 
        static juce::Font m_labelFont;
    };
}