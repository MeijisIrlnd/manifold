/*
  ==============================================================================

    ToolTray.cpp
    Created: 28 Oct 2022 4:15:00pm
    Author:  letsm

  ==============================================================================
*/

#include "ToolTray.h"
#include <Macros.h>
namespace Manifold::UI
{
    ToolTray::ToolTray()
    {
        // Aw shit here we go again...
        for (auto i = 0; i < static_cast<int>(TOOL::NUM_ELEMENTS); i++)
        {
            auto associatedTool = s_toolLookup[static_cast<TOOL>(i)];
            std::unique_ptr<ToolTrayElement> current(new ToolTrayElement(associatedTool.imageData.first, associatedTool.imageData.second));
            m_toolSelector.push_back(std::move(current));
            addAndMakeVisible(m_toolSelector.back().get()); 
        }
    }

    ToolTray::~ToolTray()
    {
    }
    void ToolTray::paint(MANIFOLD_UNUSED juce::Graphics& g)
    {
    }
    void ToolTray::resized()
    {
        auto toolWidth = static_cast<int>(getWidth() / m_toolSelector.size());
        for (auto i = 0; i < m_toolSelector.size(); i++) {
            int xPos = static_cast<int>(i * toolWidth);
            m_toolSelector[i]->setBounds(xPos, 0, toolWidth, getHeight());
        }
    }

    ToolTray::ToolTrayElement::ToolTrayElement(const void* iconData, int iconSize)
    {
        m_icon = juce::ImageCache::getFromMemory(iconData, iconSize);

    }
    ToolTray::ToolTrayElement::~ToolTrayElement()
    {
    }

    void ToolTray::ToolTrayElement::paint(juce::Graphics& g)
    {
        juce::Rectangle<float> iconBounds(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
        g.drawImage(m_icon.rescaled(getWidth(), getHeight()), iconBounds);
        if (m_highlighted) {
            g.fillAll(juce::Colour(0x7F7F7F7F));
        }
    }

    void ToolTray::ToolTrayElement::resized()
    {
    }
}