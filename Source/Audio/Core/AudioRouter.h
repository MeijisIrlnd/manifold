/*
  ==============================================================================

    AudioRouter.h
    Created: 11 Jun 2022 3:53:47am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Manifold::Audio::Core
{
    class AudioRouter
    {
    public: 
        AudioRouter(juce::AudioProcessorGraph& graph);
    private: 
        juce::AudioProcessorGraph& m_graph;
    };
}