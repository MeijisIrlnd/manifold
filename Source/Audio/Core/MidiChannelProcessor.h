/*
  ==============================================================================

    MidiChannelProcessor.h
    Created: 9 May 2022 2:39:29am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "AudioChannelProcessor.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core 
        {
            class MidiChannelProcessor : public BaseChannelProcessor
            {
            public: 
                MidiChannelProcessor(InternalChannel* associatedChannel);
                void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
                void processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages) override;
                void releaseResources() override;

            private: 
                
            };
        }
    }
}