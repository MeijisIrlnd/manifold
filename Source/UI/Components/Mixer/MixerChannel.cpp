/*
  ==============================================================================

    MixerChannel.cpp
    Created: 7 May 2022 4:31:32pm
    Author:  Syl

  ==============================================================================
*/

#include "MixerChannel.h"
#include <UI/LookAndFeel/MixerLF.h>
namespace Manifold
{
    namespace UI
    {       
        MixerChannel::MixerChannel(Manifold::Audio::InternalChannel* associatedChannel) :
            m_channel(associatedChannel),
            m_muteButton(BinaryData::MuteOff_png, BinaryData::MuteOff_pngSize,
                BinaryData::MuteOn_png, BinaryData::MuteOn_pngSize),
            m_soloButton(BinaryData::SoloOff_png, BinaryData::SoloOff_pngSize,
                BinaryData::SoloOn_png, BinaryData::SoloOn_pngSize),
            m_colourPicker(associatedChannel),
            m_insertPluginList(associatedChannel->getId(), 4),
            m_sendList(associatedChannel->getId(), 4)
        {
            m_volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
            m_volumeSlider.setRange(0, 1, 0.01);
            m_volumeSlider.setValue(GET_PARAM_AS_VALUE(associatedChannel, "volume").getValue(), juce::dontSendNotification);
            m_volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
            addAndMakeVisible(&m_volumeSlider);
            m_volumeSlider.onValueChange = [this] {GET_PARAM_AS_VALUE(m_channel, "volume").setValue(m_volumeSlider.getValue()); };

            m_panSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
            m_panSlider.setRange(0, 1, 0.01);
            m_panSlider.setValue(GET_PARAM_AS_VALUE(m_channel, "pan").getValue(), juce::dontSendNotification);
            m_panSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
            addAndMakeVisible(&m_panSlider);
            m_panSlider.onValueChange = [this] {GET_PARAM_AS_VALUE(m_channel, "pan").setValue(m_panSlider.getValue()); };
            m_panText.setImage(juce::ImageCache::getFromMemory(BinaryData::PanText_png, BinaryData::PanText_pngSize));
            addAndMakeVisible(&m_panText);

            addAndMakeVisible(&m_muteButton);
            m_muteButton.addListener(this);
            addAndMakeVisible(&m_soloButton);
            m_soloButton.addListener(this);

            addAndMakeVisible(&m_colourPicker);
            m_colourPicker.addListener(this);

            addAndMakeVisible(&m_insertPluginList);
            addAndMakeVisible(&m_sendList);
            m_nameDisplay.setFont(dynamic_cast<MixerLF*>(&getLookAndFeel())->getOverallFont());
            m_nameDisplay.setJustification(juce::Justification::centred);
            m_nameDisplay.onTextChange = [this] { m_channel->rename(m_nameDisplay.getText().toStdString()); };
            addAndMakeVisible(&m_nameDisplay);

            addAndMakeVisible(&m_inputSelector);
            addAndMakeVisible(&m_outputSelector);
            m_inputSelectLabel.setText("Input Source", juce::dontSendNotification);
            m_inputSelectLabel.setJustificationType(juce::Justification::centred);
            addAndMakeVisible(&m_inputSelectLabel);
            m_outputSelectLabel.setText("Output Source", juce::dontSendNotification);
            m_outputSelectLabel.setJustificationType(juce::Justification::centred);
            m_outputSelector.setText("1/2");
            m_outputSelector.addListener(this);
            addAndMakeVisible(&m_outputSelectLabel);

        }

        MixerChannel::~MixerChannel()
        {
        }

        void MixerChannel::imageToggleButtonClicked(Primitives::ImageToggleButton* b, bool newState)
        {
            if (b == &m_muteButton) {
                GET_PARAM_AS_VALUE(m_channel, "mute").setValue(newState);
            }
            else if (b == &m_soloButton) {
                GET_PARAM_AS_VALUE(m_channel, "solo").setValue(newState);
            }
        }


        void MixerChannel::onColourPicked(juce::Colour& newColour)
        {
            m_channel->setColour(newColour);
            repaint();
        }

        void MixerChannel::onRoutingElementPress(RoutingElementComponent* el)
        {
            if (el == &m_outputSelector) MANIFOLD_LIKELY
            {
                handleOutputRouting(el);
            }
        }

        void MixerChannel::handleOutputRouting(RoutingElementComponent* element)
        {
            auto elements = GET_ENGINE()->getChannelsOfType(GROUP_CHANNEL);
            std::unordered_map<int, int> keyToId;
            juce::PopupMenu popup;
            int count = 0;
            popup.addItem(1, "1/2");
            for (auto it = elements.begin(); it != elements.end(); it++) {
                if (it->second != m_channel) {
                    popup.addItem(count + 2, it->second->getName());
                    keyToId.emplace(std::make_pair(count + 2, it->first));
                    ++count;
                }
            }
            popup.showMenuAsync(juce::PopupMenu::Options(), [this, element, keyToId, elements](MANIFOLD_UNUSED int res) {
                if (res == 0) return;
                if (res == 1) {
                    element->setText("1/2");
                    GET_ENGINE()->connectNodes(m_channel->getId());
                }
                else {
                    element->setText(elements.at(keyToId.at(res))->getName());
                    GET_ENGINE()->connectNodes(m_channel->getId(), elements.at(keyToId.at(res))->getId());
                }
                });
        }

        void MixerChannel::paint(juce::Graphics& g)
        {
            if (m_channel->getHasRenamed()) {
                m_nameDisplay.setText(m_channel->getName(), juce::dontSendNotification);
            }
            g.setColour(m_channel->getColour());
            g.fillAll();
            g.setColour(juce::Colours::black);
            juce::Rectangle<float> bounds(0.25f, 0.25f, static_cast<float>(getWidth() - 0.5f), static_cast<float>(getHeight() - 0.5f));
            g.drawRect(bounds, 0.25f);
        }

        void MixerChannel::drawCommonElements()
        {
            // insert
            // i/o
            // pan 
            // im, re
            // mute / solo 
            // volume 
            // colour picker
            auto elSpacing = getHeight() / 64;
            m_insertPluginList.setBounds(0, 0, getWidth(), getHeight() / 8);
            m_sendList.setBounds(0, getHeight() / 8, getWidth(), getHeight() / 8);
            auto blankSpaceY = getHeight() / 32 + (elSpacing * 2) + m_sendList.getY() + m_sendList.getHeight();
            //m_inputSelectLabel.setBounds(0, m_insertPluginList.getHeight() + m_insertPluginList.getY(), getWidth(), elSpacing);
            //m_inputSelector.setBounds(0, m_insertPluginList.getHeight() + elSpacing, getWidth(), getHeight() / 32);
            m_outputSelectLabel.setBounds(0, blankSpaceY, getWidth(), elSpacing);
            m_outputSelector.setBounds(0, blankSpaceY + elSpacing, getWidth(), getHeight() / 32);
            m_panSlider.setBounds(getWidth() / 2 - getWidth() / 6, m_outputSelector.getY() + m_outputSelector.getHeight() + elSpacing, getWidth() / 3, getWidth() / 3);
            m_muteButton.setBounds(getWidth() / 2 - getWidth() / 4, m_panSlider.getY() + m_panSlider.getHeight() + elSpacing, getWidth() / 4, getWidth() / 4);
            m_soloButton.setBounds(getWidth() / 2, m_muteButton.getY(), getWidth() / 4, getWidth() / 4);
            m_volumeSlider.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2 - getHeight() / 24);
            m_nameDisplay.setBounds(0, m_volumeSlider.getY() + m_volumeSlider.getHeight(), getWidth(), getHeight() / 48);
            m_colourPicker.setBounds(0, m_nameDisplay.getY() + m_nameDisplay.getHeight(), getWidth(), getHeight() / 48);
        }

    }
}