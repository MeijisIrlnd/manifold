/*
  ==============================================================================

    MidiChannelProcessor.cpp
    Created: 9 May 2022 2:39:29am
    Author:  Syl

  ==============================================================================
*/

#include "MidiChannelProcessor.h"

namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            MidiChannelProcessor::MidiChannelProcessor(InternalChannel* associatedChannel) :
                BaseChannelProcessor(CHANNEL_TYPE::MIDI, associatedChannel)
            {
                
            }

            void MidiChannelProcessor::prepareToPlay(double sampleRate, int samplesPerBlockExpected)
            {
                m_sampleRate = sampleRate;
                m_samplesPerBlock = samplesPerBlockExpected;
            }

            void MidiChannelProcessor::processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& messages)
            {
                if (m_pluginInstrument.get() != nullptr) {
                    m_pluginInstrument->processBlock(buffer, messages);
                    for (auto& i : m_inserts) {
                        if (i != nullptr) {
                            i->processBlock(buffer, messages);
                        }
                    }
                    buffer.applyGain(static_cast<float>(m_associatedChannel->getVolume()));
                    if (m_associatedChannel->getMuteState()) { buffer.applyGain(0.0f); }
                }
            }

            void MidiChannelProcessor::releaseResources()
            {
                for (auto& i : m_inserts) {
                    if (i != nullptr) {
                        i->releaseResources();
                    }
                }
            }
        }
    }
}