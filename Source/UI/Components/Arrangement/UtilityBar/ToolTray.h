/*
  ==============================================================================

    ToolTray.h
    Created: 28 Oct 2022 4:15:00pm
    Author:  letsm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Macros.h>
#include <Types/Arrangement/Tool.h>
namespace Manifold::UI
{
    class ToolTray : public juce::Component
    {
    public: 
        ToolTray();
        ~ToolTray() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        class ToolTrayElement : public juce::Component
        {
        public: 
            ToolTrayElement(const void* iconData, int iconSize);
            ~ToolTrayElement() override;
            MANIFOLD_INLINE void setHighlight(bool shouldHighlight) { m_highlighted = shouldHighlight; }
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            juce::Image m_icon;
            bool m_highlighted{ false };
        };
        std::vector<std::unique_ptr<ToolTrayElement> > m_toolSelector;
    };
}