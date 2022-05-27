/*
  ==============================================================================

    MidiChannelProcessor.h
    Created: 9 May 2022 2:39:29am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "BaseChannelProcessor.h"
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
                MANIFOLD_INLINE void loadSourcePlugin(std::unique_ptr<juce::AudioPluginInstance>&& sourcePlugin) {
                    m_pluginInstrument.reset(sourcePlugin.release());
                    m_pluginInstrument->prepareToPlay(m_sampleRate, m_samplesPerBlock);
                }
                MANIFOLD_INLINE juce::AudioPluginInstance* getPluginInstance() { return m_pluginInstrument.get(); }
                void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
                void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& messages) override;
                void releaseResources() override;

            private: 
                std::unique_ptr<juce::AudioPluginInstance> m_pluginInstrument;
            };
        }
    }
}