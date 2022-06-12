/*
  ==============================================================================

    AudioRouter.cpp
    Created: 11 Jun 2022 3:53:47am
    Author:  Syl

  ==============================================================================
*/

#include "AudioRouter.h"

namespace Manifold::Audio::Core
{
    AudioRouter::AudioRouter(juce::AudioProcessorGraph& graph) : m_graph(graph)
    {

    }

    // SO this yoke needs to handle the busses etc. Im not sure how the fuck busses work..
    // I THINK we'd like to be able to set a channel's input, and output. 
    // If a channel's input matches a channel's output, we connect them together.
    // We COULD just list the channels (audio and group) as options. 
    // 
}