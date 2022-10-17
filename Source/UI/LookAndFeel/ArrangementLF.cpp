/*
  ==============================================================================

    ArrangementLF.cpp
    Created: 17 Oct 2022 3:45:16am
    Author:  Syl

  ==============================================================================
*/

#include "ArrangementLF.h"
juce::Font Manifold::UI::ArrangementLF::m_labelFont = juce::Typeface::createSystemTypefaceFor(BinaryData::PixelTandysoft0rJG_ttf, BinaryData::PixelTandysoft0rJG_ttfSize);

Manifold::UI::ArrangementLF::ArrangementLF()
{
    setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
    setColour(juce::TextEditor::textColourId, juce::Colours::white);
    setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentWhite);
}
