/*
  ==============================================================================

    AudioMixerChannel.cpp
    Created: 8 May 2022 4:27:43pm
    Author:  Syl

  ==============================================================================
*/

#include "AudioMixerChannel.h"

namespace Manifold
{
    namespace UI
    {
        AudioMixerChannel::AudioMixerChannel(Manifold::Audio::InternalChannel* channel) : 
            MixerChannel(channel),
            m_inputMonitorButton(BinaryData::InputMonitorOff_png, BinaryData::InputMonitorOff_pngSize, 
                BinaryData::InputMonitorOn_png, BinaryData::InputMonitorOn_pngSize),
            m_recordEnableButton(BinaryData::RecordEnableOff_png, BinaryData::RecordEnableOff_pngSize, 
                BinaryData::RecordEnableOn_png, BinaryData::RecordEnableOn_pngSize)
        {
            addAndMakeVisible(&m_inputMonitorButton);
            addAndMakeVisible(&m_recordEnableButton);
            m_inputSelectLabel.setText("Input Source", juce::dontSendNotification);
            m_inputSelectLabel.setJustificationType(juce::Justification::centred);
            addAndMakeVisible(&m_inputSelectLabel);
            addAndMakeVisible(&m_inputSelector);
            m_inputSelector.addListener(this);
            m_outputSelector.addListener(this);
        }

        void AudioMixerChannel::imageToggleButtonClicked(Primitives::ImageToggleButton* b, bool newState)
        {
            if (b == &m_muteButton) {
                GET_PARAM_AS_VALUE(m_channel, "mute").setValue(newState);
            }
            else if (b == &m_soloButton) {
                GET_PARAM_AS_VALUE(m_channel, "solo").setValue(newState);
            }
            else if (b == &m_inputMonitorButton) {
                GET_PARAM_AS_VALUE(m_channel, "inputmonitor").setValue(newState);
            }
            else if (b == &m_recordEnableButton) {
                GET_PARAM_AS_VALUE(m_channel, "recordenable").setValue(newState);
            }
        }

        void AudioMixerChannel::onRoutingElementPress(RoutingElementComponent* element)
        {
            if (element == &m_inputSelector) {
                DBG("IP Routing pressed");
            }
            else if (element == &m_outputSelector) {
                auto elements = GET_ENGINE->getChannelsOfType(Manifold::Audio::CHANNEL_TYPE::AUDIO);
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
                    if (res == 1) { element->setText("1/2"); }
                    else {
                        element->setText(elements.at(keyToId.at(res))->getName());
                    }
                });
            }
        }

        void AudioMixerChannel::resized()
        {
            auto elSpacing = getHeight() / 64;
            drawCommonElements();
            m_inputSelectLabel.setBounds(0, m_insertPluginList.getY() + m_insertPluginList.getHeight(), getWidth(), elSpacing);
            m_inputSelector.setBounds(0, m_inputSelectLabel.getY() + m_inputSelectLabel.getHeight(), getWidth(), getHeight() / 32);
            m_inputMonitorButton.setBounds(m_muteButton.getX(), m_muteButton.getY() + m_muteButton.getHeight() + elSpacing, m_muteButton.getWidth(), m_muteButton.getHeight());
            m_recordEnableButton.setBounds(m_inputMonitorButton.getX() + m_inputMonitorButton.getWidth(), m_inputMonitorButton.getY(),
            m_inputMonitorButton.getWidth(), m_inputMonitorButton.getHeight());
        }

    }
}