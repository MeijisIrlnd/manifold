/*
  ==============================================================================

    PlayheadCursor.cpp
    Created: 8 Oct 2022 3:44:56am
    Author:  Syl

  ==============================================================================
*/

#include "PlayheadCursor.h"

namespace Manifold::UI
{
    PlayheadCursor::PlayheadCursor()
    {
        m_flagImage = juce::ImageCache::getFromMemory(BinaryData::PlayheadFlag_png, BinaryData::PlayheadFlag_pngSize);
    }

    PlayheadCursor::~PlayheadCursor()
    {
    }
    void PlayheadCursor::paint(juce::Graphics& g)
    {
        juce::Rectangle<float> imgBounds(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()/ 64.0f));
        g.drawImage(m_flagImage, imgBounds);
        g.setColour(juce::Colour(0xFF53856C));
        g.drawLine(0, 0, 0, static_cast<float>(getHeight()), 0.5f);
    }
    void PlayheadCursor::resized()
    {
        m_flagImage.rescaled(getWidth(), getHeight() / 64, juce::Graphics::highResamplingQuality);
    }
}