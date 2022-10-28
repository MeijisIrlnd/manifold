/*
  ==============================================================================

    UtilityBarComponent.cpp
    Created: 28 Oct 2022 4:11:32pm
    Author:  letsm

  ==============================================================================
*/

#include "UtilityBarComponent.h"

namespace Manifold::UI
{
    UtilityBarComponent::UtilityBarComponent()
    {
        addAndMakeVisible(&m_toolTray);
    }

    UtilityBarComponent::~UtilityBarComponent()
    {
    }

    void UtilityBarComponent::paint(MANIFOLD_UNUSED juce::Graphics& g)
    {
    }

    void UtilityBarComponent::resized()
    {
        m_toolTray.setBounds(getWidth() / 4, 0, getWidth() / 2, getHeight());
    }
}