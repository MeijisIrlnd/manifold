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
        MixerView::MixerView()
        {
            setLookAndFeel(&m_lf);
            GET_ENGINE->addListener(this);
        }
        MixerView::~MixerView()
        {
            setLookAndFeel(nullptr);
            GET_ENGINE->removeListener(this);
        }

        void MixerView::onChannelCreated(Manifold::Audio::InternalChannel* newChannel)
        {
            std::unique_ptr<MixerChannel> current(new MixerChannel(newChannel));
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
                m_mixerChannels[i]->setBounds((getWidth() / 16) * i, 0, getWidth() / 16, getHeight());
            }
        }
    }
}

