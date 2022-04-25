/*
  ==============================================================================

    PositionTracker.h
    Created: 23 Apr 2022 2:53:50am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Macros.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            class PositionTracker : public juce::ChangeBroadcaster
            {
            public: 

                bool getIsRunning() const { return m_running; }

                MANIFOLD_INLINE void prepare(double sampleRate) { m_sampleRate = sampleRate; }

                MANIFOLD_INLINE void toggle(bool state) {
                    m_running = state;
                }

                MANIFOLD_INLINE void toggle() {
                    m_running = !m_running;
                }

                MANIFOLD_INLINE void operator++() { 
                    ++m_sampleCounter;
                    sendChangeMessage();
                }

                MANIFOLD_INLINE void operator+=(juce::uint64 x) { 
                    m_sampleCounter += x; 
                    DBG(m_sampleCounter);
                    sendChangeMessage();
                }

                MANIFOLD_INLINE PositionTracker& operator=(juce::uint64 x) {
                    m_sampleCounter = x;
                    sendChangeMessage();
                    return *this;
                }

                MANIFOLD_INLINE const double getSampleRate() const { return m_sampleRate; }

            private: 
                bool m_running = false;
                double m_sampleRate;
                juce::uint64 m_sampleCounter = 0;
            };
        }
    }
}