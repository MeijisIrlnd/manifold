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

        void PluginListComponentItem::mouseUp(const juce::MouseEvent& ev)
        {
            if (ev.mods.isRightButtonDown()) {
                m_vstContextMenu.clear();
                juce::KnownPluginList& vstList = GET_ENGINE->getVstList();
                
                std::function<void(int)> userCallback = [this](int result) {
                    juce::KnownPluginList& vstList = GET_ENGINE->getVstList();
                    juce::Array<juce::PluginDescription> descriptions = vstList.getTypes();
                    MANIFOLD_UNUSED auto chosenIndex = vstList.getIndexChosenByMenu(descriptions, result);
                    if (chosenIndex == -1) { return; }
                    m_readout.setText(descriptions[chosenIndex].name, juce::dontSendNotification);
                    GET_ENGINE->loadPlugin(m_channelId, m_slotIndex, chosenIndex);
                };
                
                vstList.addToMenu(m_vstContextMenu, vstList.getTypes(), juce::KnownPluginList::sortAlphabetically);
                m_vstContextMenu.showMenuAsync(juce::PopupMenu::Options(), userCallback);
            }
            else if (ev.mods.isLeftButtonDown()) {
                // Open the plugin's editor...
                GET_ENGINE->createEditorForPlugin(m_channelId, m_slotIndex);
            }
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