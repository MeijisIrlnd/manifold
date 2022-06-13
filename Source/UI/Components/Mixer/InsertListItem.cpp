/*
  ==============================================================================

    InsertListItem.cpp
    Created: 13 Jun 2022 3:20:30am
    Author:  Syl

  ==============================================================================
*/

#include "InsertListItem.h"

namespace Manifold::UI
{
    InsertListItem::InsertListItem(const int id, const int index) : 
        ListItem(id, index)
    {
    }

    void InsertListItem::mouseUp(const juce::MouseEvent& ev)
    {
        if (ev.mods.isRightButtonDown()) {
            m_vstContextMenu.clear();
            juce::KnownPluginList& vstList = GET_ENGINE()->getPluginList();
            juce::Array<juce::PluginDescription> filtered = GET_ENGINE()->getFilteredDescriptions(false);
            std::function<void(int)> userCallback = [this, filtered](int result) {
                juce::KnownPluginList& vstList = GET_ENGINE()->getPluginList();
                MANIFOLD_UNUSED auto chosenIndex = vstList.getIndexChosenByMenu(filtered, result);
                if (chosenIndex == -1) { return; }
                m_readout.setText(filtered[chosenIndex].name, juce::dontSendNotification);
                auto current = filtered[chosenIndex];
                GET_ENGINE()->loadPlugin(m_channelId, m_slotIndex, current);
            };

            vstList.addToMenu(m_vstContextMenu, filtered, juce::KnownPluginList::sortAlphabetically);
            m_vstContextMenu.showMenuAsync(juce::PopupMenu::Options(), userCallback);
        }
        else if (ev.mods.isLeftButtonDown()) {
            // Open the plugin's editor...
            GET_ENGINE()->createEditorForPlugin(m_channelId, m_slotIndex);
        }
    }
}