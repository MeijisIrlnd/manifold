/*
  ==============================================================================

    ListItem.h
    Created: 13 Jun 2022 3:13:02am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Audio/ManifoldEngine.h"
namespace Manifold::UI
{
    class ListItem : public juce::Component
    {
    public:
        ListItem(const int channelId, const int slotIndex);
        virtual ~ListItem() override;
        virtual void mouseUp(const juce::MouseEvent& ev) override = 0;
        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;
    protected: 
        const int m_channelId;
        const int m_slotIndex;
        juce::Image m_background;
        juce::Label m_readout;
    };
}