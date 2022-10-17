/*
  ==============================================================================

    AudioChannelProcessor.h
    Created: 8 May 2022 6:30:32pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "BaseChannelProcessor.h"
#include "../../Macros.h"
#include "../../Types/Channel/AudioChannel.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            class AudioChannelProcessor : public BaseChannelProcessor
            {
            public: 
                AudioChannelProcessor(AudioChannel* associatedChannel);
                void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
                void processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages) override;
                void releaseResources() override;

            private: 
                juce::Value m_inputMonitor;
            };
        }
    }
}