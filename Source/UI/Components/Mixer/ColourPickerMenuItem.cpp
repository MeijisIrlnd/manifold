/*
  ==============================================================================

    ColourPickerPopup.cpp
    Created: 8 May 2022 12:17:47am
    Author:  Syl

  ==============================================================================
*/

#include "ColourPickerMenuItem.h"

namespace Manifold
{
    namespace UI
    {
        ColourPickerMenuItem::ColourPickerMenuItem(const juce::Colour& colour) :
            m_colour(colour)
        {
        }

        void ColourPickerMenuItem::getIdealSize(int& idealWidth, int& idealHeight)
        {
            idealHeight = 50;
            idealWidth = 50;
        }

        void ColourPickerMenuItem::paint(juce::Graphics& g)
        {
            g.setColour(m_colour);
            g.fillAll();
        }

        void ColourPickerMenuItem::resized()
        {
        }
    }
}

