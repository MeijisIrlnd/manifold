/*
  ==============================================================================

    AudioChannelProcessor.h
    Created: 8 May 2022 6:30:32pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ProcessorBase.h"
#include "../../Macros.h"
#include "../../Types/Channel/AudioChannel.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            class AudioChannelProcessor : public ProcessorBase
            {
            public: 
                AudioChannelProcessor(AudioChannel* associatedChannel);
                void loadPlugin(int slotIndex, std::unique_ptr<juce::AudioPluginInstance>&& plugin);
                void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
                void processBlock(juce::AudioSampleBuffer& buffer, MANIFOLD_UNUSED juce::MidiBuffer& messages) override;
                void releaseResources() override;

            private: 
                AudioChannel* m_associatedChannel{ nullptr };
                std::vector<std::unique_ptr<juce::AudioPluginInstance> > m_inserts;
            };
        }
    }
}