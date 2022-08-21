/*
  ==============================================================================

    PianoRollComponent.h
    Created: 9 Jul 2022 10:34:57pm
    Author:  letsm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Types/Channel/MidiChannel.h"
namespace Manifold::UI::Components
{
    class PianoRollComponent : public juce::Component
    {
    public: 
        PianoRollComponent(Manifold::Audio::MidiChannel* associatedChannel);
        ~PianoRollComponent() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        Manifold::Audio::MidiChannel* m_associatedChannel{ nullptr };
    };
}