/*
  ==============================================================================

    MainWindowComponent.h
    Created: 22 Apr 2022 1:37:01am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Utils/UIListener.h"
#include "Components/TransportComponent.h"
#include "../Audio/ManifoldEngine.h"
namespace Manifold
{
    namespace UI
    {
        class MainWindowComponent : public juce::Component
        {
        public: 
            MainWindowComponent(UIListener* uiListener, Manifold::Audio::ManifoldEngine& engine);
            ~MainWindowComponent() override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private:
            TransportComponent m_transportComponent;
            Manifold::Audio::ManifoldEngine& m_engine;
        };
    }
}