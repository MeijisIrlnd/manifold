/*
  ==============================================================================

    TimelineComponent.cpp
    Created: 23 Aug 2022 1:57:15am
    Author:  Syl

  ==============================================================================
*/

#include "TimelineComponent.h"

namespace Manifold::UI
{
    TimelineComponent::TimelineComponent()
    {
        Audio::Core::PositionTracker::getInstance()->m_bpm.addChangeListener(this);
        Audio::Core::PositionTracker::getInstance()->m_timeSig.addChangeListener(this);
    }
    TimelineComponent::~TimelineComponent()
    {
    }
    void TimelineComponent::changeListenerCallback(MANIFOLD_UNUSED juce::ChangeBroadcaster* broadcaster)
    {
        // Dont bother checking, we already know it was either bpm or time sig that changed and both need redraws..
        repaint();
    }

    void TimelineComponent::paint(juce::Graphics& g)
    {
        // Right, here come the calculations...
        // How long is a beat?? 
        juce::Rectangle<int> topRect(0, 0, getWidth(), getHeight() / 24);
        g.setColour(juce::Colours::black);
        g.fillRect(topRect);
        using namespace Audio::Core;
        auto bpm = PositionTracker::getInstance()->getBpm();
        auto timeSig = PositionTracker::getInstance()->getTimeSignature();
        double quarterNoteLen = 60 / bpm;
        // And how many bars do we need to show? 
        // That depends on the time amt to show, how many quarters fit into that? 
        auto numQuartersInTimeframe = m_timeAmtToShow / quarterNoteLen;
        // SO we draw that many, sick, so lets start drawing ticks for now...
        auto spacing = static_cast<float>(getWidth() / numQuartersInTimeframe);
        float xPos = 0;
        g.setColour(juce::Colours::white);
        int currentBarNum = 0;
        for (auto i = 0; i < numQuartersInTimeframe; i++, xPos += spacing)
        {
            if (i % timeSig.first == 0) {
                ++currentBarNum;
            }
            juce::Line<float> line(xPos, 0, xPos, static_cast<float>(getHeight()));
            g.drawLine(line);
            juce::Rectangle<int> m_textRect(static_cast<int>(xPos), 0, getWidth() / 32, getHeight() / 8);
            std::stringstream formattedText;
            formattedText << currentBarNum << "." << (i % timeSig.first) + 1;
            g.drawText(formattedText.str(), m_textRect, juce::Justification::centredTop);

        }
    }
    void TimelineComponent::resized()
    {
    }
}