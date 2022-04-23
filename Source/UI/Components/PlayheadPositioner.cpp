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

        void PlayheadPositioner::changeListenerCallback(juce::ChangeBroadcaster* source)
        {
        }

        void PlayheadPositioner::paint(juce::Graphics& g)
        {
        }

        void PlayheadPositioner::resized()
        {
        }
    }
}

