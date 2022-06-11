/*
  ==============================================================================

    MixerChannel.cpp
    Created: 7 May 2022 4:31:32pm
    Author:  Syl

  ==============================================================================
*/

#include "MixerChannel.h"

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
            m_insertPluginList(associatedChannel->getId())
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

            m_panText.setImage(juce::ImageCache::getFromMemory(BinaryData::PanText_png, BinaryData::PanText_pngSize));
            addAndMakeVisible(&m_panText);

            addAndMakeVisible(&m_muteButton);
            m_muteButton.addListener(this);
            addAndMakeVisible(&m_soloButton);
            m_soloButton.addListener(this);

            addAndMakeVisible(&m_colourPicker);
            m_colourPicker.addListener(this);

            addAndMakeVisible(&m_insertPluginList);
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

        void MixerChannel::paint(juce::Graphics& g)
        {
            g.setColour(m_channel->getColour());
            g.fillAll();
            g.setColour(juce::Colours::black);
            juce::Rectangle<float> bounds(0.25f, 0.25f, static_cast<float>(getWidth() - 0.5f), static_cast<float>(getHeight() - 0.5f));
            g.drawRect(bounds, 0.25f);
        }

        void MixerChannel::drawCommonElements()
        {
            m_insertPluginList.setBounds(0, 0, getWidth(), getHeight() / 4);
            m_muteButton.setBounds(getWidth() / 2 - getWidth() / 4, getHeight() / 2 - getWidth() / 6 - getHeight() / 32, getWidth() / 4, getWidth() / 4);
            m_soloButton.setBounds(getWidth() / 2, m_muteButton.getY(), getWidth() / 4, getWidth() / 4);
            // Some spacing for Input mon and record enable / vst select 
            // Assume same height, and spacing.. 
            int spacing = m_soloButton.getHeight() + getHeight() / 32;
            m_panSlider.setBounds(getWidth() / 2 - getWidth() / 6, m_soloButton.getY() - getHeight() / 32 - getWidth() / 3 - spacing, getWidth() / 3, getWidth() / 3);
            m_panText.setBounds(getWidth() / 2 - getWidth() / 6, m_panSlider.getY() - m_panSlider.getHeight(), getWidth() / 3, getHeight() / 24);
            m_volumeSlider.setBounds(0, static_cast<int>(getHeight() * 0.5f), getWidth(), getHeight() / 2 - getHeight() / 32);
            m_colourPicker.setBounds(0, m_volumeSlider.getY() + m_volumeSlider.getHeight(), getWidth(), getHeight() / 32);
        }
    }
}