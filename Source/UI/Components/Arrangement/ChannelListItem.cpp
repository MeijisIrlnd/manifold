/*
  ==============================================================================

    ChannelListItem.cpp
    Created: 24 Apr 2022 9:37:15pm
    Author:  Syl

  ==============================================================================
*/

#include "ChannelListItem.h"
#include <UI/LookAndFeel/ArrangementLF.h>
namespace Manifold
{
    namespace UI
    {
        namespace Components
        {
            ChannelListItem::ChannelListItem(Manifold::Audio::InternalChannel* internalChannel) : 
                m_internal(internalChannel)
            {
                m_nameLabel.setFont(dynamic_cast<ArrangementLF*>(&getLookAndFeel())->getOverallFont());
                m_nameLabel.setText(internalChannel->getName());
                m_nameLabel.onTextChange = [this] { 
                    m_internal->rename(m_nameLabel.getText().toStdString());
                };
                addAndMakeVisible(&m_nameLabel);
            }

            ChannelListItem::~ChannelListItem()
            {
            }

            void ChannelListItem::paint(juce::Graphics& g)
            {
                //g.setColour(juce::Colours::blanchedalmond);
                if (m_internal->getHasRenamed()) {
                    m_nameLabel.setText(m_internal->getName(), juce::dontSendNotification);
                }
                g.fillAll(m_internal->getColour());
            }

            void ChannelListItem::resized()
            {

                m_nameLabel.setBounds(0, 0, getWidth(), getHeight() / 4);
            }
        }
    }
}