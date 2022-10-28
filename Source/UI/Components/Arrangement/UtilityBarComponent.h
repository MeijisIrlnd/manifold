/*
  ==============================================================================

    UtilityBarComponent.h
    Created: 28 Oct 2022 4:11:31pm
    Author:  letsm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <UI/Components/Arrangement/UtilityBar/ToolTray.h>
namespace Manifold::UI
{
    class UtilityBarComponent : public juce::Component
    {
    public: 
        UtilityBarComponent();
        ~UtilityBarComponent() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        ToolTray m_toolTray;
    };
}