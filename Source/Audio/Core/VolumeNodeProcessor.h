/*
  ==============================================================================

    VolumeNodeProcessor.h
    Created: 12 Jun 2022 10:59:56pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "ProcessorBase.h"
#include "../../Types/Channel/InternalChannel.h"
namespace Manifold::Audio::Core 
{
    class VolumeNodeProcessor : public ProcessorBase
    {
    public: 
        VolumeNodeProcessor(InternalChannel* associatedChannel);
        void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
        void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& midiBuffer) override;
        void releaseResources() override;
    private: 
        InternalChannel* m_associatedChannel{ nullptr };
        juce::Value m_volume;
    };
}