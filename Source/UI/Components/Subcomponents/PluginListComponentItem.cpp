/*
  ==============================================================================

    PluginListComponentItem.cpp
    Created: 8 May 2022 1:03:08am
    Author:  Syl

  ==============================================================================
*/

#include "PluginListComponentItem.h"

namespace Manifold
{
    namespace UI
    {
        PluginListComponentItem::PluginListComponentItem()
        {
            m_background = juce::ImageCache::getFromMemory(BinaryData::VSTSlotBackground_png,
                BinaryData::VSTSlotBackground_pngSize);

        }

        PluginListComponentItem::~PluginListComponentItem()
        {
        }

        void PluginListComponentItem::paint(juce::Graphics& g)
        {
            juce::Rectangle<float> targetArea(
                0.0f,
                0.0f,
                static_cast<float>(getWidth()), 
                static_cast<float>(getHeight())
            );
            g.drawImage(m_background, targetArea);
        }

        void PluginListComponentItem::resized()
        {
        }

    }
}