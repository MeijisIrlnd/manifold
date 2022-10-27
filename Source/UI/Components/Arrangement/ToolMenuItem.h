/*
  ==============================================================================

    ToolMenuItem.h
    Created: 27 Oct 2022 1:06:31am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Types/Tools.h>
namespace Manifold::UI
{
    class ToolMenuItem : public juce::PopupMenu::CustomComponent
    {
    public:
        ToolMenuItem(TOOL tool, const void* iconData, int iconSize);
        ~ToolMenuItem() override;
        void getIdealSize(int& idealWidth, int& idealHeight) override;
        void paint(juce::Graphics& g) override;
        void resized() override;
        
    private:
        TOOL m_tool;
        juce::Image m_icon;
        bool m_isMouseOver{ false };
    };
}