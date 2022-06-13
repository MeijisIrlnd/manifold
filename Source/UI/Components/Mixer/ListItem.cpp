/*
  ==============================================================================

    ListItem.cpp
    Created: 13 Jun 2022 3:13:02am
    Author:  Syl

  ==============================================================================
*/

#include "ListItem.h"

namespace Manifold::UI
{
    ListItem::ListItem(const int channelId, const int slotIndex) :
        m_channelId(channelId),
        m_slotIndex(slotIndex)
    {
        m_background = juce::ImageCache::getFromMemory(BinaryData::VSTSlotBackground_png,
            BinaryData::VSTSlotBackground_pngSize);

        m_readout.setInterceptsMouseClicks(false, false);
        addAndMakeVisible(&m_readout);
    }

    ListItem::~ListItem()
    {
    }

    void ListItem::paint(juce::Graphics& g)
    {
        juce::Rectangle<float> targetArea(
            0.0f,
            0.0f,
            static_cast<float>(getWidth()),
            static_cast<float>(getHeight())
        );
        g.drawImage(m_background, targetArea);
    }

    void ListItem::resized()
    {
        m_readout.setBounds(getWidth() / 8, 0, getWidth() - getWidth() / 8, getHeight());
    }
}