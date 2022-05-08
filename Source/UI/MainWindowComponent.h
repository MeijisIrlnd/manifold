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
#include "Views/ArrangementView.h"
#include "Views/MixerView.h"
#include "Components/PluginWindowManager.h"

namespace Manifold
{
    namespace UI
    {
        class MainWindowComponent : public juce::Component, public juce::KeyListener,
            public Manifold::Audio::EngineListener
        {
        public: 
            MainWindowComponent(UIListener* uiListener);
            ~MainWindowComponent() override;
            void onPluginUIOpened(juce::AudioProcessor* processor) override;
            bool keyPressed(const juce::KeyPress& key, juce::Component* fromComponent) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            TransportComponent m_transportComponent;
            ArrangementView m_arrangementView;
            MixerView m_mixerView;
            std::vector<std::shared_ptr<juce::AudioProcessorEditor> > pluginUIs;
            PluginWindowManager m_pluginWindowManager;
        };
    }
}