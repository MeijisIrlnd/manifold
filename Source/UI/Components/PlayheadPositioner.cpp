/*
  ==============================================================================

    PlayheadPositioner.cpp
    Created: 23 Apr 2022 4:14:31am
    Author:  Syl

  ==============================================================================
*/

#include "PlayheadPositioner.h"

namespace Manifold
{
    namespace UI
    {

        PlayheadPositioner::PlayheadPositioner(Manifold::Audio::Core::PositionTracker* positionTracker) : 
            m_positionTracker(positionTracker)
        {
            m_positionTracker->addChangeListener(this);
        }

        PlayheadPositioner::~PlayheadPositioner()
        {
        }

        void PlayheadPositioner::changeListenerCallback(MANIFOLD_UNUSED juce::ChangeBroadcaster* source)
        {
        }

        void PlayheadPositioner::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::red);
            g.drawLine(getWidth() / 2.0f, 0.0f, getWidth() / 2.0f, static_cast<float>(getHeight()), 0.5f);
        }

        void PlayheadPositioner::resized()
        {
        }
    }
}

