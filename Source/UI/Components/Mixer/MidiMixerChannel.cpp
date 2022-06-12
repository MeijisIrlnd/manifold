/*
  ==============================================================================

    MidiMixerChannel.cpp
    Created: 8 May 2022 4:28:30pm
    Author:  Syl

  ==============================================================================
*/

#include "MidiMixerChannel.h"

namespace Manifold
{
    namespace UI
    {
        MidiMixerChannel::MidiMixerChannel(Manifold::Audio::InternalChannel* channel) : 
            MixerChannel(channel), 
            m_instrumentButton(BinaryData::InstrumentSelect_png, BinaryData::InstrumentSelect_pngSize)
        {
            addAndMakeVisible(&m_instrumentButton);
            m_instrumentButton.addListener(this);
        }

        void MidiMixerChannel::imageButtonClicked(Primitives::ImageButton* b)
        {
            if (b == &m_instrumentButton) {
                GET_ENGINE->createEditorForMidiChannelPlugin(m_channel->getId());
            }
        }

        void MidiMixerChannel::resized()
        {
            drawCommonElements();
            m_instrumentButton.setBounds(m_muteButton.getX() + m_muteButton.getWidth() / 2, m_muteButton.getY() + m_muteButton.getHeight() + getHeight() / 64, m_muteButton.getWidth(), m_muteButton.getHeight());
        }
    }
}