/*
  ==============================================================================

    PluginContainerWindow.h
    Created: 8 May 2022 11:51:26pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../../Macros.h"
#include "BaseWindow.h"
namespace Manifold
{
    namespace UI
    {
        class PluginContainerWindow : public BaseWindow
        {
        public:
            PluginContainerWindow(const juce::String& name, juce::AudioProcessor* audioProcessor, WindowListener* listener);
            
            MANIFOLD_INLINE void closeButtonPressed() { 
                if (m_listener != nullptr) {
                    m_listener->onWindowClosed(this);
                }
            }
        private: 
            std::unique_ptr<juce::AudioProcessorEditor> m_editor{ nullptr };
        };
    }
}