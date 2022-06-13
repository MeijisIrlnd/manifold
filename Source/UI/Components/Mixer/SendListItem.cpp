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

    void SendListItem::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
    {
    }
}