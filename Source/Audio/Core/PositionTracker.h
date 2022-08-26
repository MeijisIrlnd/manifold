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

namespace Manifold::Audio::Core
{
    class PositionTracker : public juce::ChangeBroadcaster, public juce::ChangeListener
    {
    protected:
        PositionTracker() {
            m_bpm = 120;
            m_timeSig = std::make_pair(7, 4);
        }
    public:
        ~PositionTracker();
        PositionTracker(const PositionTracker& other) = delete;
        PositionTracker(PositionTracker&& other) = delete;
        PositionTracker& operator=(const PositionTracker& other) = delete;
        MANIFOLD_INLINE static void startup() { getInstance(); }
        static PositionTracker* getInstance();
        static void shutdown();
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
    
        MANIFOLD_INLINE double getBpm() { return m_bpm.get(); }
    
        MANIFOLD_INLINE void setTimeSignature(std::pair<int, int>& newTimeSig) { m_timeSig = newTimeSig; }
        MANIFOLD_INLINE std::pair<int, int>& getTimeSignature() { return m_timeSig.get(); }
        BroadcastVariable<double> m_bpm;
        BroadcastVariable<std::pair<int, int> > m_timeSig;
    private:
        static std::mutex m_mutex;
        static PositionTracker* m_instance;
        bool m_running = false;
        double m_sampleRate{ 0 };
        juce::uint64 m_sampleCounter = 0;
        //double m_bpm{ 120 };
        //std::pair<int, int> m_timeSig;D
    };
}