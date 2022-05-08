/*
  ==============================================================================

    PluginWindowManager.cpp
    Created: 9 May 2022 12:35:20am
    Author:  Syl

  ==============================================================================
*/

#include "PluginWindowManager.h"

namespace Manifold
{
    namespace UI
    {
        PluginWindowManager::PluginWindowManager()
        {
        }

        void PluginWindowManager::addWindow(juce::AudioProcessor* audioProcessor)
        {
            std::unique_ptr<PluginContainerWindow> currentWindow(new PluginContainerWindow("Test", audioProcessor));
            currentWindow->addListener(this);
            currentWindow->setAlwaysOnTop(true);
            m_windows.push_back(std::move(currentWindow));
        }

        void PluginWindowManager::onWindowClosed(PluginContainerWindow* window)
        {
            auto predicate = [window](std::unique_ptr<PluginContainerWindow>& toFind) { return toFind.get() == window; };
            auto it = std::find_if(m_windows.begin(), m_windows.end(), predicate);
            if (it != m_windows.end()) {
                m_windows.erase(it);
            }

        }
    }
}