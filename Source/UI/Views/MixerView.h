/*
  ==============================================================================

    MixerView.h
    Created: 26 Apr 2022 2:12:32am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Audio/ManifoldEngine.h"
#include "../Components/Mixer/AudioMixerChannel.h"
#include "../Components/Mixer/MidiMixerChannel.h"
#include "../Components/Mixer/GroupMixerChannel.h"
#include "../LookAndFeel/MixerLF.h"
#include "../../Macros.h"
namespace Manifold
{
    namespace UI
    {
        class MixerView : public juce::Component,
            public Manifold::Audio::EngineListener
        {
        public: 
            MixerView(int& mixerChannelWidth);
            ~MixerView() override;
            MANIFOLD_INLINE const int getNumChannels() { return static_cast<int>(m_mixerChannels.size()); }
            void onChannelCreated(Manifold::Audio::InternalChannel* newChannel) override;
            void onChannelDeleted(Manifold::Audio::InternalChannel* toDelete) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            int& m_mixerChannelWidth;
            MixerLF m_lf;
            std::vector<std::unique_ptr<MixerChannel> > m_mixerChannels;
        };
    }
}