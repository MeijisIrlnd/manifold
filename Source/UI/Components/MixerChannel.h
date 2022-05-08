/*
  ==============================================================================

    MixerChannel.h
    Created: 7 May 2022 4:31:32pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Types/Channel/InternalChannel.h"
#include "../Primitives/ImageButton.h"
#include "Subcomponents/ColourPicker.h"
#include "../Primitives/ButtonListener.h"
#include "Subcomponents/InsertPluginList.h"
namespace Manifold
{
    namespace UI
    {
        class MixerChannel : public juce::Component, 
            public Manifold::UI::Primitives::ButtonListener, 
            public juce::Slider::Listener,
            public ColourPickerListener
        {
        public: 
            MixerChannel(Manifold::Audio::InternalChannel* associatedChannel);
            ~MixerChannel() override;
            void imageToggleButtonClicked(Primitives::ImageToggleButton* b, bool newState) override;
            void sliderValueChanged(juce::Slider* slider) override;
            void onColourPicked(juce::Colour& newColour) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            Manifold::Audio::InternalChannel* m_channel{ nullptr };
            juce::TextEditor m_nameDisplay;
            juce::ImageComponent m_panText;
            juce::Slider m_volumeSlider;
            juce::Slider m_panSlider;
            Manifold::UI::Primitives::ImageToggleButton m_muteButton;
            Manifold::UI::Primitives::ImageToggleButton m_soloButton;
            ColourPicker m_colourPicker;
            InsertPluginList m_insertPluginList;
            //0xFFF5F5DC -> Beige 
            //0xFF1C2541 ->Midnight Blurp
            //0XFFEF626C ->Salmon of knowledge
            //0xFF519E8A ->Greenish
            //0xFF8A95a5 ->Silver
        };
    }
}