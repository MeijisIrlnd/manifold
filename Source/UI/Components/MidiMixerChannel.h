/*
  ==============================================================================

    MidiMixerChannel.h
    Created: 8 May 2022 4:28:30pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "MixerChannel.h"

namespace Manifold
{
    namespace UI
    {
        class MidiMixerChannel : public MixerChannel
        {
        public: 
            MidiMixerChannel(Manifold::Audio::InternalChannel* channel);
            void resized() override;
        private: 
            Manifold::UI::Primitives::ImageButton m_instrumentButton;
        };
    }
}