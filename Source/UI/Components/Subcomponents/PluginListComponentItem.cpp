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
        PluginListComponentItem::PluginListComponentItem(const int channelId, const int slotIndex) : 
            m_channelId(channelId),
            m_slotIndex(slotIndex)
        {
            m_background = juce::ImageCache::getFromMemory(BinaryData::VSTSlotBackground_png,
                BinaryData::VSTSlotBackground_pngSize);

            m_readout.setInterceptsMouseClicks(false, false);
            addAndMakeVisible(&m_readout);
        }

        PluginListComponentItem::~PluginListComponentItem()
        {
        }

        void PluginListComponentItem::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
        {
            m_vstContextMenu.clear();
            std::unordered_map<std::string, std::string>& vsts = GET_ENGINE->getVstList();
            for (auto it = vsts.begin(); it != vsts.end(); it++) {
                std::string currentKey = it->first;
                std::function<void()> callback = [currentKey, this] {
                    GET_ENGINE->loadVst(m_channelId, m_slotIndex, currentKey);
                    m_readout.setText(currentKey, juce::dontSendNotification);
                };
                m_vstContextMenu.addItem(it->first, callback);
                
            }
            m_vstContextMenu.showMenuAsync(juce::PopupMenu::Options());
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
            m_readout.setBounds(getWidth() / 8, 0, getWidth() - getWidth() / 8, getHeight());
        }

    }
}