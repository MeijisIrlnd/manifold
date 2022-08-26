/*
  ==============================================================================

    OverallLF.cpp
    Created: 9 May 2022 4:17:10am
    Author:  Syl

  ==============================================================================
*/

#include "OverallLF.h"

namespace Manifold
{
    namespace UI
    {
        OverallLF::OverallLF()
        {
            m_scrollbarThumb = juce::ImageCache::getFromMemory(BinaryData::ScrollbarThumb_png, BinaryData::ScrollbarThumb_pngSize);
            setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
            setColour(juce::TextEditor::textColourId, juce::Colours::white);
            setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentWhite);
        }

        void OverallLF::drawScrollbar(juce::Graphics& g, juce::ScrollBar& scrollbar, int x, int y, int width, int height, bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown)
        {
            using namespace juce;
            ignoreUnused(isMouseDown);

            Rectangle<int> thumbBounds;

            if (isScrollbarVertical)
                thumbBounds = { x, thumbStartPosition, width, thumbSize };
            else
                thumbBounds = { thumbStartPosition, y, thumbSize, height };

            auto c = scrollbar.findColour(ScrollBar::ColourIds::thumbColourId);
            g.setColour(isMouseOver ? c.brighter(0.25f) : c);
            g.drawImage(m_scrollbarThumb,
                juce::Rectangle<float>(static_cast<float>(thumbBounds.getX()), 
                    static_cast<float>(thumbBounds.getY()), 
                    static_cast<float>(thumbBounds.getWidth()), 
                    static_cast<float>(thumbBounds.getHeight())));
        }
    }
}