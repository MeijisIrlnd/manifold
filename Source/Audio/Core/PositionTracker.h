/*
  ==============================================================================

    PositionTracker.h
    Created: 23 Apr 2022 2:53:50am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <mutex>
#include <JuceHeader.h>
#include "../../Macros.h"
#include "../../Types/BroadcastVariable.h"

namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            class PositionTracker : public juce::ChangeBroadcaster, public juce::ChangeListener
            {
            protected:
                PositionTracker() {
                   // m_bpm.addChangeListener(this);
                   // m_timeSig.addChangeListener(this);
                }
            public:
                ~PositionTracker();
                PositionTracker(const PositionTracker& other) = delete;
                PositionTracker(PositionTracker&& other) = delete;
                PositionTracker& operator=(const PositionTracker& other) = delete;
                MANIFOLD_INLINE static void startup() { getInstance(); }
                static PositionTracker* getInstance();
                bool getIsRunning() const { return m_running; }

                void changeListenerCallback(juce::ChangeBroadcaster* source) override {
                    if (source == nullptr) { return; }
                }

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

                MANIFOLD_INLINE void setBpm(double newBpm) {
                    m_bpm = newBpm; 
                }

                MANIFOLD_INLINE const double getBpm() const { return m_bpm; }

                MANIFOLD_INLINE void setTimeSignature(std::pair<int, int>& newTimeSig) { m_timeSig = newTimeSig; }
                MANIFOLD_INLINE const std::pair<int, int>& getTimeSignature() const { return m_timeSig; }
            private: 
                static std::mutex m_mutex;
                static PositionTracker* m_instance;
                bool m_running = false;
                double m_sampleRate{ 0 };
                juce::uint64 m_sampleCounter = 0;
                double m_bpm{ 120 };
                std::pair<int, int> m_timeSig;
                //BroadcastVariable<double> m_bpm;
                //BroadcastVariable<std::pair<int, int> > m_timeSig{ std::make_pair(4, 4) };
            };
        }
    }
}