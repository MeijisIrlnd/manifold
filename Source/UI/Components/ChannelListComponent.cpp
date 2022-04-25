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
        ChannelListComponent::ChannelListComponent(Manifold::Audio::ManifoldEngine& engine) : 
            m_engine(engine)
        {
        }
        ChannelListComponent::~ChannelListComponent()
        {
        }

        void ChannelListComponent::mouseUp(const juce::MouseEvent& ev)
        {
            if (ev.mods.isRightButtonDown()) {
                DBG("Right click");
                juce::PopupMenu popup;
                popup.addItem(1, "Create audio channel");
                popup.addItem(2, "Something else");
                popup.showMenuAsync(juce::PopupMenu::Options(), [this](int res) {
                    switch (res) {
                        case 1: 
                        {
                            DBG("Creating new audio channel");
                            Manifold::Audio::InternalChannel* newChannel = m_engine.createChannel();
                            std::unique_ptr<ChannelListItem> uiItem(new ChannelListItem(newChannel));
                            m_channelListItems.push_back(std::move(uiItem));
                            addAndMakeVisible(m_channelListItems.back().get());
                            resized();
                            // Also add it and make it visible, and draw it 
                            break;
                        }
                        case 2: 
                        {
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
                g.drawLine(0, (getHeight() / 12) * i, getWidth(), (getHeight() / 12) * i);
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