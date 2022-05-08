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
        }

        void AudioMixerChannel::resized()
        {
            drawCommonElements();
            m_inputMonitorButton.setBounds(m_muteButton.getX(), m_muteButton.getY() - getHeight() / 16, m_muteButton.getWidth(), m_muteButton.getHeight());
            m_recordEnableButton.setBounds(m_inputMonitorButton.getX() + m_inputMonitorButton.getWidth(), m_inputMonitorButton.getY(),
                m_inputMonitorButton.getWidth(), m_inputMonitorButton.getHeight());
        }
    }
}