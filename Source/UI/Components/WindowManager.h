/*
  ==============================================================================

    PluginWindowManager.h
    Created: 9 May 2022 12:35:20am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <mutex>
#include "PluginContainerWindow.h"
#include "SettingsWindow.h"
#define GET_WINDOW_MANAGER() Manifold::UI::WindowManager::getInstance()
namespace Manifold
{
    namespace UI
    {
        class WindowManager : public WindowListener
        {
        protected: 
            WindowManager();
        public: 
            ~WindowManager();
            WindowManager(WindowManager& other) = delete;
            void operator=(const WindowManager& other) = delete;
            static WindowManager* getInstance();
            static void shutdown();
            void addSettingsWindow();
            void addPluginWindow(juce::AudioProcessor* audioProcessor);
            void onWindowClosed(BaseWindow* window) override;
        private: 
            static std::mutex m_mutex;
            static WindowManager* m_instance;
            std::vector<std::unique_ptr<BaseWindow> > m_windows;
        };
    }
}