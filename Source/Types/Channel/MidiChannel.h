/*
  ==============================================================================

    MidiChannel.h
    Created: 8 May 2022 4:10:47am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "InternalChannel.h"

namespace Manifold
{
    namespace Audio
    {
        class MidiChannel : public InternalChannel
        {
        public: 
            MidiChannel(int internalId, std::string name);
            MidiChannel(const MidiChannel& other);
            MANIFOLD_INLINE void addInputConnection(const Connection& connection) {
                m_inputConnections.push_back(connection);
            }
            MANIFOLD_INLINE std::vector<Connection>& getInputConnections() {
                return m_inputConnections;
            }

        private: 
            std::vector<Connection> m_inputConnections;
            juce::MidiMessageSequence m_midiInfo;
        };
    }
}