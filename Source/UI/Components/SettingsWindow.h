/*
  ==============================================================================

    SettingsWindow.h
    Created: 27 May 2022 1:53:00am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Audio/ManifoldEngine.h"
#include "../../Macros.h"
#include "BaseWindow.h"
namespace Manifold
{
    namespace UI
    {
        class SettingsWindow;
        class SettingsWindowContainer : public BaseWindow
        {
        public: 
            SettingsWindowContainer(const juce::String& name, WindowListener* listener);
            void closeButtonPressed() override;

        private: 
            std::unique_ptr<SettingsWindow> m_window;
        };

        class SettingsWindow : public juce::Component
        {
        public: 
            SettingsWindow(juce::AudioDeviceManager& deviceManager);
            ~SettingsWindow() override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            juce::AudioDeviceManager& m_deviceManager;
            juce::AudioDeviceSelectorComponent m_selector;
        };
    }
}