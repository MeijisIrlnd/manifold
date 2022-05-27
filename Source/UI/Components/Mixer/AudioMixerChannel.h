/*
  ==============================================================================

    AudioMixerChannel.h
    Created: 8 May 2022 4:27:43pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "MixerChannel.h"
namespace Manifold
{
    namespace UI
    {
        class AudioMixerChannel : public MixerChannel
        {
        public: 
            AudioMixerChannel(Manifold::Audio::InternalChannel* channel);

            void resized() override;
        private:
            Manifold::UI::Primitives::ImageToggleButton m_inputMonitorButton;
            Manifold::UI::Primitives::ImageToggleButton m_recordEnableButton;
        };
    }
}