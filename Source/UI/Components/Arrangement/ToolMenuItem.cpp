/*
  ==============================================================================

    ToolMenuItem.cpp
    Created: 27 Oct 2022 1:06:31am
    Author:  Syl

  ==============================================================================
*/

#include "ToolMenuItem.h"
namespace Manifold::UI
{
    ToolMenuItem::ToolMenuItem(const void* iconData, int iconSize)
    {
        m_icon = juce::ImageCache::getFromMemory(iconData, iconSize);
    }

    ToolMenuItem::~ToolMenuItem()
    {
    }

    void ToolMenuItem::getIdealSize(int& idealWidth, int& idealHeight)
    {
        idealWidth = 30;
        idealHeight = 30;
    }

    void ToolMenuItem::paint(juce::Graphics& g)
    {
        g.fillAll(juce::Colours::white);
        juce::Rectangle<float> targetArea(0.0f, 0.0f, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
        g.drawImage(m_icon, targetArea);
        if (isItemHighlighted()) {
            g.fillAll(juce::Colour(0x7F7F7F7F));
        }
    }

    void ToolMenuItem::resized()
    {
    }
}