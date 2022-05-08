/*
  ==============================================================================

    PluginContainerWindow.cpp
    Created: 8 May 2022 11:51:26pm
    Author:  Syl

  ==============================================================================
*/

#include "PluginContainerWindow.h"

namespace Manifold
{
    namespace UI
    {
        PluginContainerWindow::PluginContainerWindow(const juce::String& name, juce::AudioProcessor* audioProcessor) : 
            juce::DocumentWindow(name, juce::Colours::black, 7)
        {
            m_editor.reset(audioProcessor->createEditor());
            setContentNonOwned(m_editor.get(), true);
            setSize(200, 200);
            setVisible(true);
        }
    }

}