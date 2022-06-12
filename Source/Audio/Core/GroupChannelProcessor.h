/*
  ==============================================================================

    GroupChannelProcessor.h
    Created: 11 Jun 2022 3:39:23am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "BaseChannelProcessor.h"
#include "../../Types/Channel/GroupChannel.h"
namespace Manifold::Audio::Core
{
    class GroupChannelProcessor : public BaseChannelProcessor
    {
    public: 
        GroupChannelProcessor(GroupChannel* internalChannel);
        void prepareToPlay(double sampleRate, int samplesPerBlockExpected) override;
        void processBlock(juce::AudioSampleBuffer& buffer, juce::MidiBuffer& messages) override;
        void releaseResources() override;
    private: 

    };
}