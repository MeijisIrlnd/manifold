/*
  ==============================================================================

    PlayheadPositioner.cpp
    Created: 23 Apr 2022 4:14:31am
    Author:  Syl

  ==============================================================================
*/

#include "PlayheadPositioner.h"

namespace Manifold
{
    namespace UI
    {

        PlayheadPositioner::PlayheadPositioner() : m_sampleCounter(GET_POSITION_TRACKER()->getSampleCounter())
        {
            startTimer(1);
            addAndMakeVisible(&m_cursor);
        }

        PlayheadPositioner::~PlayheadPositioner()
        {
        }

        void PlayheadPositioner::timerCallback()
        {
            repaint();
        }

        void PlayheadPositioner::paint(juce::Graphics& g)
        {
            
            g.setColour(juce::Colours::green);
            auto timeSeconds = m_sampleCounter / GET_POSITION_TRACKER()->getSampleRate();
            if (m_shownTimeRange.first < timeSeconds && m_shownTimeRange.second > timeSeconds) {
                // Okay WHERE do we draw it? 
                // Scale from time range to x, y 
                auto x = static_cast<float>(juce::jmap<double>(timeSeconds, m_shownTimeRange.first, m_shownTimeRange.second, 0, static_cast<double>(getWidth())));
                m_cursor.setBounds(static_cast<int>(x), 0, getWidth() / 84, getHeight());
                //g.drawLine(x, 0, x, static_cast<float>(getHeight()), 0.5f);
            }
        }

        void PlayheadPositioner::resized()
        {
        }
    }
}

