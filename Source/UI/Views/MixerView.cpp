/*
  ==============================================================================

    MixerView.cpp
    Created: 26 Apr 2022 2:12:32am
    Author:  Syl

  ==============================================================================
*/

#include "MixerView.h"

namespace Manifold
{
    namespace UI
    {
        MixerView::MixerView(int& mixerChannelWidth) : 
            m_mixerChannelWidth(mixerChannelWidth)
        {
            setLookAndFeel(&m_lf);
            GET_ENGINE()->addListener(this);
        }
        MixerView::~MixerView()
        {
            setLookAndFeel(nullptr);
            GET_ENGINE()->removeListener(this);
        }

        void MixerView::onChannelCreated(Manifold::Audio::InternalChannel* newChannel)
        {
            std::unique_ptr<MixerChannel> current;
            switch (newChannel->getChannelType()) {
            case AUDIO_CHANNEL: 
                current.reset(dynamic_cast<MixerChannel*>(new AudioMixerChannel(newChannel)));
                break;
            case MIDI_CHANNEL: 
                current.reset(dynamic_cast<MixerChannel*>(new MidiMixerChannel(newChannel)));
                break;
            case GROUP_CHANNEL: 
                current.reset(dynamic_cast<MixerChannel*>(new GroupMixerChannel(newChannel)));
                break;
            }

            m_mixerChannels.push_back(std::move(current));
            addAndMakeVisible(m_mixerChannels.back().get());
            resized();

        }
        void MixerView::onChannelDeleted(MANIFOLD_UNUSED Manifold::Audio::InternalChannel* toDelete)
        {
        }
        void MixerView::paint(juce::Graphics& g)
        {
            g.fillAll(juce::Colours::beige);
        }

        void MixerView::resized()
        {
            for (auto i = 0; i < m_mixerChannels.size(); i++) {
                m_mixerChannels[i]->setBounds((m_mixerChannelWidth) * i, 0, m_mixerChannelWidth, getHeight());
            }
        }
    }
}

