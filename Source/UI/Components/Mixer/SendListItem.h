/*
  ==============================================================================

    SendListItem.h
    Created: 13 Jun 2022 3:12:43am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ListItem.h"

namespace Manifold::UI
{
    class SendListItem : public ListItem 
    {
    public: 
        SendListItem(const int id, const int index);
        void mouseUp(const juce::MouseEvent& ev) override;
    private: 
        juce::PopupMenu m_popup;
    };
}