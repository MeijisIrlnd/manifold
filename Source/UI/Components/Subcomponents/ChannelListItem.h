/*
  ==============================================================================

    ChannelListItem.h
    Created: 24 Apr 2022 9:37:15pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Types/Channel/InternalChannel.h"

namespace Manifold
{
    namespace UI
    {
        namespace Components
        {
            class ChannelListItem : public juce::Component
            {
            public: 
                ChannelListItem(Manifold::Audio::InternalChannel* internalChannel);
                ~ChannelListItem() override;
                void paint(juce::Graphics& g) override;
                void resized() override;
            private: 
                Manifold::Audio::InternalChannel* m_internal = nullptr;
                juce::TextEditor m_nameLabel;
                // Solo and mute buttons..
            };
        }
    }
}