/*
  ==============================================================================

    BaseChannelProcessor.h
    Created: 8 May 2022 8:38:06pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ProcessorBase.h"
#include "../../Types/Channel/InternalChannel.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            class BaseChannelProcessor : public ProcessorBase
            {
            public: 
                BaseChannelProcessor(CHANNEL_TYPE type, InternalChannel* internalChannel);
                virtual ~BaseChannelProcessor();

                MANIFOLD_INLINE virtual void loadPlugin(int slotIndex, std::unique_ptr<juce::AudioPluginInstance>&& plugin) {
                    m_inserts[slotIndex].reset(plugin.release());
                    m_inserts[slotIndex]->enableAllBuses();
                    m_inserts[slotIndex]->prepareToPlay(m_sampleRate, m_samplesPerBlock);
                }

                MANIFOLD_INLINE CHANNEL_TYPE getType() const { return m_type; }
                virtual void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override = 0;
                virtual void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& messages) override = 0;
                virtual void releaseResources() override = 0;

            protected:
                CHANNEL_TYPE m_type;
                InternalChannel* m_associatedChannel{ nullptr };
                
                std::vector<std::unique_ptr<juce::AudioPluginInstance> > m_inserts;
                juce::Value m_volume, m_pan, m_mute, m_solo;

            };
        }
    }
}