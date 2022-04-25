/*
  ==============================================================================

    ChannelListItem.cpp
    Created: 24 Apr 2022 9:37:15pm
    Author:  Syl

  ==============================================================================
*/

#include "ChannelListItem.h"

namespace Manifold
{
    namespace UI
    {
        namespace Components
        {
            ChannelListItem::ChannelListItem(Manifold::Audio::InternalChannel* internalChannel) : 
                m_internal(internalChannel)
            {
                m_nameLabel.setText(internalChannel->getName());
                addAndMakeVisible(&m_nameLabel);
            }

            ChannelListItem::~ChannelListItem()
            {
            }

            void ChannelListItem::paint(juce::Graphics& g)
            {
                g.setColour(juce::Colours::blanchedalmond);
                g.fillAll();
            }

            void ChannelListItem::resized()
            {
                m_nameLabel.setBounds(0, 0, getWidth(), getHeight() / 4);
            }
        }
    }
}