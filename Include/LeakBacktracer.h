/*
  ==============================================================================

    LeakBacktracer.h
    Created: 4 Feb 2022 5:11:02pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class AdvancedLeakDetector {
public:
    AdvancedLeakDetector() {
        getBackTraceHash().set((void*)this, juce::SystemStats::getStackBacktrace());
    }
    ~AdvancedLeakDetector() {
        getBackTraceHash().remove((void*)this);
    }
private:
    typedef juce::HashMap<void*, juce::String> BackTraceHash;
    struct HashHolder {
        ~HashHolder() {
            if (traces.size() > 0)
            {
                /* Memory leak info. */
                DBG("Found " + juce::String(traces.size()) + " possible leaks");
                for (BackTraceHash::Iterator i(traces); i.next();)
                {
                    DBG("-----");
                    DBG(i.getValue());
                }
                jassertfalse;
            }
        }
        BackTraceHash traces;
    };
    BackTraceHash& getBackTraceHash() {
        static HashHolder holder;
        return holder.traces;
    }
};
