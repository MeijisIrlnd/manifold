/*
  ==============================================================================

    MixerChannel.h
    Created: 7 May 2022 4:31:32pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#include "../../../Types/Channel/InternalChannel.h"
#include "../../Primitives/ImageButton.h"
#include "ColourPicker.h"
#include "../../Primitives/ButtonListener.h"
#include "MixerList.h"
#include "InsertListItem.h"
#include "SendListItem.h"
#include "RoutingElementComponent.h"
namespace Manifold
{
    namespace UI
    {
        class MixerChannel : public juce::Component, 
            public Manifold::UI::Primitives::ButtonListener, 
            public ColourPickerListener,
            public RoutingElementComponent::Listener
        {
        public: 
            MixerChannel(Manifold::Audio::InternalChannel* associatedChannel);
            virtual ~MixerChannel() override;
            MANIFOLD_INLINE Manifold::Audio::CHANNEL_TYPE getChannelType() { return m_channel->getChannelType(); }
            void imageToggleButtonClicked(Primitives::ImageToggleButton* b, bool newState) override;
            void onColourPicked(juce::Colour& newColour) override;
            virtual void onRoutingElementPress(RoutingElementComponent* el);
            void paint(juce::Graphics& g) override;
            virtual void resized() override = 0;

        protected:
            void drawCommonElements();
            void handleOutputRouting(RoutingElementComponent* element);
            Manifold::Audio::InternalChannel* m_channel{ nullptr };
            juce::TextEditor m_nameDisplay;
            juce::ImageComponent m_panText;
            juce::Slider m_volumeSlider;
            juce::Slider m_panSlider;
            Manifold::UI::Primitives::ImageToggleButton m_muteButton;
            Manifold::UI::Primitives::ImageToggleButton m_soloButton;
            std::unique_ptr<juce::SliderParameterAttachment> m_volumeAttachment{ nullptr }, m_panAttachment{nullptr};
            ColourPicker m_colourPicker;
            MixerList<InsertListItem> m_insertPluginList;
            MixerList<SendListItem> m_sendList;
            RoutingElementComponent m_inputSelector, m_outputSelector;
            juce::Label m_inputSelectLabel, m_outputSelectLabel;
            //0xFFF5F5DC -> Beige 
            //0xFF1C2541 ->Midnight Blurp
            //0XFFEF626C ->Salmon of knowledge
            //0xFF519E8A ->Greenish
            //0xFF8A95a5 ->Silver
        };
    }
}