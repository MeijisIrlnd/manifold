/*
  ==============================================================================

    PlayheadCursor.h
    Created: 8 Oct 2022 3:44:56am
    Author:  Syl

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
namespace Manifold::UI
{
    class PlayheadCursor : public juce::Component
    {
    public: 
        PlayheadCursor();
        ~PlayheadCursor() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::Image m_flagImage;
    };
}