/*
  ==============================================================================

    RoutingElementComponent.h
    Created: 12 Jun 2022 12:37:36am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Primitives/ImageButton.h"
namespace Manifold::UI
{
    
    class RoutingElementComponent : public juce::Component, public Manifold::UI::Primitives::ButtonListener
    {
    public: 
        struct Listener {
            virtual ~Listener() {}
            virtual void onRoutingElementPress(RoutingElementComponent* component) = 0;
        };
        RoutingElementComponent();
        ~RoutingElementComponent() override;
        MANIFOLD_INLINE void addListener(Listener* newListener) { m_listener = newListener; }
        MANIFOLD_INLINE void setText(const std::string& newText) { m_text.setText(newText, juce::dontSendNotification); }
        void imageButtonClicked(MANIFOLD_UNUSED Manifold::UI::Primitives::ImageButton* b) override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::Label m_text;
        Manifold::UI::Primitives::ImageButton m_button;
        RoutingElementComponent::Listener* m_listener;
    };
}