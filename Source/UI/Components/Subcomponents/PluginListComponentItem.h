/*
  ==============================================================================

    PluginListComponentItem.h
    Created: 8 May 2022 1:03:08am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Manifold
{
    namespace UI
    {
        class PluginListComponentItem : public juce::Component
        {
        public: 
            PluginListComponentItem();
            ~PluginListComponentItem() override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            juce::Image m_background;
        };
    }
}