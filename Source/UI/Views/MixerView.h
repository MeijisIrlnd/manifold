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
#include "../Components/AudioMixerChannel.h"
#include "../Components/MidiMixerChannel.h"
#include "../LookAndFeel/MixerLF.h"
namespace Manifold
{
    namespace UI
    {
        class MixerView : public juce::Component,
            public Manifold::Audio::EngineListener
        {
        public: 
            MixerView();
            ~MixerView() override;
            void onChannelCreated(Manifold::Audio::InternalChannel* newChannel) override;
            void onChannelDeleted(Manifold::Audio::InternalChannel* toDelete) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            MixerLF m_lf;
            std::vector<std::unique_ptr<MixerChannel> > m_mixerChannels;
        };
    }
}