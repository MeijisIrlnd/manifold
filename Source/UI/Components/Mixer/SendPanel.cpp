/*
  ==============================================================================

    SendPanel.cpp
    Created: 14 Jun 2022 12:36:17am
    Author:  Syl

  ==============================================================================
*/

#include "SendPanel.h"
namespace Manifold::UI
{
    SendPanel::SendPanel(const int channelId, const int slotIndex) :
        m_channel(channelId), m_slot(slotIndex),
        m_aflButton(BinaryData::PFLIcon_png, BinaryData::PFLIcon_pngSize,
            BinaryData::AFLIcon_png, BinaryData::AFLIcon_pngSize)
    {
        addAndMakeVisible(&m_aflButton);
    }

    SendPanel::~SendPanel()
    {
        
    }

    void SendPanel::paint(MANIFOLD_UNUSED juce::Graphics& g)
    {
    }

    void SendPanel::resized()
    {
    }
}