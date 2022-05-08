/*
  ==============================================================================

    PluginContainerWindow.h
    Created: 8 May 2022 11:51:26pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Macros.h"
namespace Manifold
{
    namespace UI
    {
        class PluginContainerWindow;
        struct PluginContainerListener
        {
            virtual ~PluginContainerListener() {} 
            virtual void onWindowClosed(MANIFOLD_UNUSED PluginContainerWindow* window) = 0;
        };

        class PluginContainerWindow : public juce::DocumentWindow
        {
        public:
            PluginContainerWindow(const juce::String& name, juce::AudioProcessor* audioProcessor);
            MANIFOLD_INLINE void addListener(PluginContainerListener* newListener) { m_listener = newListener; }
            MANIFOLD_INLINE void closeButtonPressed() { 
                if (m_listener != nullptr) {
                    m_listener->onWindowClosed(this);
                }
            }
        private: 
            std::unique_ptr<juce::AudioProcessorEditor> m_editor{ nullptr };
            PluginContainerListener* m_listener{ nullptr };
        };
    }
}