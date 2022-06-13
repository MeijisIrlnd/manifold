/*
  ==============================================================================

    SendListItem.cpp
    Created: 13 Jun 2022 3:12:43am
    Author:  Syl

  ==============================================================================
*/

#include "SendListItem.h"

namespace Manifold::UI
{
    SendListItem::SendListItem(const int id, const int index) : 
        ListItem(id, index)
    {
    }

    void SendListItem::mouseUp(const juce::MouseEvent& ev)
    {
        if (ev.mods.isRightButtonDown()) {
            m_popup.clear();
            auto channelList = GET_ENGINE()->getChannelsOfType(GROUP_CHANNEL);
            std::unordered_map<int, Manifold::Audio::InternalChannel*> idToEl;
            auto count = 1;
            for (auto it = channelList.begin(); it != channelList.end(); it++) {
                if (it->second->getId() != m_channelId) { // Also need to verify that the other channel isn't sending to this one.. 
                    m_popup.addItem(count, it->second->getName());
                    idToEl[count] = it->second;
                    ++count;
                }
            }
            std::function<void(int)> callback = [this, idToEl](int result) {
                if (result == -1) return;
                GET_ENGINE()->addSend(m_channelId, idToEl.at(result)->getId());
                m_readout.setText(idToEl.at(result)->getName(), juce::dontSendNotification);
            };
            m_popup.showMenuAsync(juce::PopupMenu::Options(), callback);
        }
    }
}