/*
  ==============================================================================

    SendPanel.h
    Created: 14 Jun 2022 12:36:17am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Primitives/ImageButton.h"
namespace Manifold::UI
{
    class SendPanel : public juce::Component
    {
    public: 
        SendPanel(const int channelId, const int slotIndex);
        ~SendPanel() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        const int m_channel;
        const int m_slot;
        juce::Slider m_sendLevelSlider;
        Primitives::ImageToggleButton m_aflButton;
    };
}