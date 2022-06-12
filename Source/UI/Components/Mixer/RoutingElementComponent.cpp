/*
  ==============================================================================

    RoutingElementComponent.cpp
    Created: 12 Jun 2022 12:37:36am
    Author:  Syl

  ==============================================================================
*/

#include "RoutingElementComponent.h"

namespace Manifold::UI
{
    RoutingElementComponent::RoutingElementComponent() : 
        m_button(BinaryData::VSTSlotBackground_png, BinaryData::VSTSlotBackground_pngSize)
    {
        m_text.setText("Test", juce::dontSendNotification);
        m_text.setInterceptsMouseClicks(false, false);
        addAndMakeVisible(&m_button);
        m_button.addListener(this);
        addAndMakeVisible(&m_text);
    }

    RoutingElementComponent::~RoutingElementComponent()
    {
    }

    void RoutingElementComponent::imageButtonClicked(MANIFOLD_UNUSED Manifold::UI::Primitives::ImageButton* b)
    {
        if (m_listener != nullptr) MANIFOLD_LIKELY {
            m_listener->onRoutingElementPress(this);
        }
    }

    void RoutingElementComponent::paint(MANIFOLD_UNUSED juce::Graphics& g)
    {
    }

    void RoutingElementComponent::resized()
    {
        m_button.setBounds(0, 0, getWidth(), getHeight());
        m_text.setBounds(getWidth() / 8, 0, getWidth(), getHeight());
    }
}