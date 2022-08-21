/*
  ==============================================================================

    AudioDriver.h
    Created: 23 Apr 2022 3:05:08am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "ProcessorBase.h"
#include "PositionTracker.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            class AudioDriver : public ProcessorBase
            {
            public: 
                AudioDriver();
                ~AudioDriver() override;
                const juce::String getName() { return "AudioDriver"; }
                void prepareToPlay(double sampleRate, int samplesPerBlock) override;
                void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& messages) override;
                void releaseResources() override;
            private: 
            };
        }
    }
}