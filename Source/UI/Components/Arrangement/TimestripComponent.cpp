/*
  ==============================================================================

    TimestripComponent.cpp
    Created: 23 Apr 2022 4:34:12pm
    Author:  Syl

  ==============================================================================
*/
#include "../../../Macros.h"
#include "TimestripComponent.h"

namespace Manifold
{
    namespace UI
    {
        TimestripComponent::TimestripComponent()
        {
        }

        TimestripComponent::~TimestripComponent()
        {
        }

        void TimestripComponent::onZoomLevelChanged(MANIFOLD_UNUSED double newZoom)
        {
            
        }

        void TimestripComponent::paint(MANIFOLD_UNUSED juce::Graphics& g)
        {
            // Decide on the timescale: at 1, show N seconds of audio (or n beats, converted to seconds...)
            // Zoom 1 = 1 beat..

        }

        void TimestripComponent::resized()
        {
        }

    }
}
