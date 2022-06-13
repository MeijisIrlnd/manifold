/*
  ==============================================================================

    InsertListItem.h
    Created: 13 Jun 2022 3:20:30am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ListItem.h"
namespace Manifold::UI
{
    class InsertListItem : public ListItem
    {
    public: 
        InsertListItem(const int id, const int index);
        void mouseUp(const juce::MouseEvent& ev) override;
    private: 
        juce::PopupMenu m_vstContextMenu;
    };
}