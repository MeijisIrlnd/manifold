/*
  ==============================================================================

    ChannelListComponent.cpp
    Created: 24 Apr 2022 9:00:33pm
    Author:  Syl

  ==============================================================================
*/

#include "ChannelListComponent.h"

namespace Manifold
{
    namespace UI
    {
        ChannelListComponent::ChannelListComponent()
        {
            GET_ENGINE->addListener(this);
        }
        ChannelListComponent::~ChannelListComponent()
        {
            GET_ENGINE->removeListener(this);
        }

        void ChannelListComponent::onChannelCreated(Manifold::Audio::InternalChannel* newChannel)
        {
            std::unique_ptr<ChannelListItem> uiItem(new ChannelListItem(newChannel));
            m_channelListItems.push_back(std::move(uiItem));
            addAndMakeVisible(m_channelListItems.back().get());
            resized();
        }

        void ChannelListComponent::onChannelDeleted(MANIFOLD_UNUSED Manifold::Audio::InternalChannel* toDelete)
        {
        }


        void ChannelListComponent::mouseUp(const juce::MouseEvent& ev)
        {
            if (ev.mods.isRightButtonDown()) {
                DBG("Right click");
                juce::PopupMenu popup;
                popup.addItem(1, "Create audio channel");
                popup.addItem(2, "Create midi channel");
                popup.showMenuAsync(juce::PopupMenu::Options(), [this](int res) {
                    switch (res) {
                        case 1: 
                        {
                            DBG("Creating new audio channel");
                            GET_ENGINE->createChannel(AUDIO_CHANNEL);
                            break;
                        }
                        case 2: 
                        {
                            GET_ENGINE->createChannel(MIDI_CHANNEL);
                            break;
                        }
                        default: 
                        {
                            break;
                        }
                    }
                });
            }
        }
        void ChannelListComponent::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::lightgreen);
            g.fillAll();
            g.setColour(juce::Colours::black);
            for (auto i = 1; i < 12; i++) {
                g.drawLine(0, (getHeight() / 12.0f) * i, static_cast<float>(getWidth()), (getHeight() / 12.0f) * i);
            }
        }
        void ChannelListComponent::resized()
        {
            for (auto i = 0; i < m_channelListItems.size(); i++) {
                m_channelListItems[i]->setBounds(0, (getHeight() / 12) * i, getWidth(), getHeight() / 12);
            }
        }
    }
}