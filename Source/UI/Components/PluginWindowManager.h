/*
  ==============================================================================

    PluginWindowManager.h
    Created: 9 May 2022 12:35:20am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "PluginContainerWindow.h"
namespace Manifold
{
    namespace UI
    {
        class PluginWindowManager : public PluginContainerListener
        {
        public: 
            PluginWindowManager();
            void addWindow(juce::AudioProcessor* audioProcessor);
            void onWindowClosed(PluginContainerWindow* window) override;
        private: 
            std::vector<std::unique_ptr<PluginContainerWindow> > m_windows;
        };
    }
}