/*
  ==============================================================================

    SettingsWindow.cpp
    Created: 27 May 2022 1:53:00am
    Author:  Syl

  ==============================================================================
*/

#include "SettingsWindow.h"
#include "../../../Audio/ManifoldEngine.h"
namespace Manifold
{
    namespace UI
    {
        enum class SETTINGS_PAGES
        {
            DEVICE
        };

        SettingsWindowContainer::SettingsWindowContainer(const juce::String& name, WindowListener* listener) : 
            BaseWindow(name, juce::Colours::lightgrey, 7, WINDOW_TYPE::SETTINGS, listener)
        {
            
            m_window.reset(new SettingsWindow(GET_ENGINE->getDeviceManager()));
            m_window->setSize(500, 900);
            setContentNonOwned(m_window.get(), true);
            setVisible(true);
        }

        void SettingsWindowContainer::closeButtonPressed()
        {
            if (m_listener != nullptr) {
                m_listener->onWindowClosed(dynamic_cast<BaseWindow*>(this));
            }
        }

        SettingsWindow::SettingsWindow(juce::AudioDeviceManager& deviceManager) : 
            m_deviceManager(deviceManager),
            m_selector(deviceManager, 1, 2, 1, 2, true, true, true, true)
        {
            addAndMakeVisible(&m_selector);
        }

        SettingsWindow::~SettingsWindow()
        {
        }
        void SettingsWindow::paint(MANIFOLD_UNUSED juce::Graphics& g)
        {
            g.fillAll(juce::Colours::darkslategrey);
        }
        void SettingsWindow::resized()
        {
            m_selector.setBounds(getLocalBounds());
        }
    }
}