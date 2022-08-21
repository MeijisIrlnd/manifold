/*
  ==============================================================================

    PianoRollComponent.cpp
    Created: 9 Jul 2022 10:34:57pm
    Author:  letsm

  ==============================================================================
*/

#include "PianoRollComponent.h"

namespace Manifold::UI::Components
{
    PianoRollComponent::PianoRollComponent(Manifold::Audio::MidiChannel* associatedChannel) : m_associatedChannel(associatedChannel)
    {
        // SO this thing should essentially be an endless scroll on the horizontal axis, with the same divisions as the main arrange view..
    }

    PianoRollComponent::~PianoRollComponent()
    {
    }

    void PianoRollComponent::paint(MANIFOLD_UNUSED juce::Graphics& g)
    {
    }
    void PianoRollComponent::resized()
    {
    }
}