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