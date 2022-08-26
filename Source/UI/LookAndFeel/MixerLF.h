/*
  ==============================================================================

    MixerLF.h
    Created: 7 May 2022 7:00:11pm
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
        class MixerLF : public juce::LookAndFeel_V4
        {
        public: 
            MixerLF();
            void drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
                float sliderPos,
                float minSliderPos,
                float maxSliderPos,
                const juce::Slider::SliderStyle style, juce::Slider& slider);

            void drawRotarySlider(juce::Graphics&, int x, int y, int width, int height,
                float sliderPosProportional, float rotaryStartAngle,
                float rotaryEndAngle, juce::Slider&) override;

            MANIFOLD_INLINE juce::Font getOverallFont() { return m_labelFont;  }
            MANIFOLD_INLINE juce::Font getLabelFont(MANIFOLD_UNUSED juce::Label& l) override {
                return m_labelFont.withHeight(18.0f);
            }

            MANIFOLD_INLINE juce::Font getPopupMenuFont() override
            { 
                return m_labelFont.withHeight(12.0f);
            }
        private: 
            juce::Image m_vThumb;
            juce::Image m_rThumb;
            static juce::Font m_labelFont;
        };
    }
}