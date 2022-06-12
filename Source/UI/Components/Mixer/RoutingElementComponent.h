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
    class RoutingElementComponent : public juce::Component
    {
    public: 
        RoutingElementComponent(const std::string& titleText);
        ~RoutingElementComponent() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::Label m_titleLabel;
        juce::Label m_text;
        Manifold::UI::Primitives::ImageButton m_button;
    };
}