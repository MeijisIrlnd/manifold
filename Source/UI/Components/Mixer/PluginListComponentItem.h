/*
  ==============================================================================

    PluginListComponentItem.h
    Created: 8 May 2022 1:03:08am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Audio/ManifoldEngine.h"
#include "../../../Macros.h"
#include "../../../Settings/Pathing.h"
namespace Manifold
{
    namespace UI
    {

        class PluginListComponentItem : public juce::Component
        {
        public: 
            PluginListComponentItem(const int channelId, const int slotIndex);
            ~PluginListComponentItem() override;
            void mouseUp(const juce::MouseEvent& ev) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            const int m_channelId;
            const int m_slotIndex;
            juce::Image m_background;
            juce::PopupMenu m_vstContextMenu;
            juce::Label m_readout;
        };
    }
}