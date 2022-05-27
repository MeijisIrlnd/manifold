/*
  ==============================================================================

    PluginWindowManager.cpp
    Created: 9 May 2022 12:35:20am
    Author:  Syl

  ==============================================================================
*/

#include "WindowManager.h"

namespace Manifold
{
    namespace UI
    {
        std::mutex WindowManager::m_mutex;
        WindowManager* WindowManager::m_instance{ nullptr };

        WindowManager::WindowManager()
        {
        }
        WindowManager::~WindowManager()
        {
        }

        WindowManager* WindowManager::getInstance()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            if (m_instance == nullptr) {
                m_instance = new WindowManager();
            }
            return m_instance;
        }

        void WindowManager::shutdown()
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            delete m_instance;
        }
        
        void WindowManager::addSettingsWindow()
        {
            std::unique_ptr<SettingsWindowContainer> current(new SettingsWindowContainer("Settings", this));
            current->setAlwaysOnTop(true);
            m_windows.push_back(std::move(current));
        }

        void WindowManager::addPluginWindow(juce::AudioProcessor* audioProcessor)
        {
            std::unique_ptr<PluginContainerWindow> currentWindow(new PluginContainerWindow("Test", audioProcessor, this));
            currentWindow->setAlwaysOnTop(true);
            m_windows.push_back(std::move(currentWindow));
        }

        void WindowManager::onWindowClosed(BaseWindow* window)
        {
            auto predicate = [window](std::unique_ptr<BaseWindow>& toFind) { return toFind.get() == window; };
            auto it = std::find_if(m_windows.begin(), m_windows.end(), predicate);
            if (it != m_windows.end()) {
                m_windows.erase(it);
            }

        }
    }
}