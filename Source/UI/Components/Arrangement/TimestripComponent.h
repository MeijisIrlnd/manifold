/*
  ==============================================================================

    TimestripComponent.h
    Created: 23 Apr 2022 4:34:12pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ZoomManager.h"
namespace Manifold
{
    namespace UI
    {
        class TimestripComponent : public juce::Component, public ZoomManager::Listener
        {
        public: 
            TimestripComponent();
            ~TimestripComponent() override;
            void onZoomLevelChanged(double newZoom) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            double m_timeAmtToDisplay{ 0 };
        };
    }
}