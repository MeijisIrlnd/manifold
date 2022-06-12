/*
  ==============================================================================

    AudioChannel.h
    Created: 8 May 2022 4:10:40am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "InternalChannel.h"
namespace Manifold
{
    namespace Audio
    {
        class AudioChannel : public InternalChannel
        {
        public: 
            AudioChannel(int internalId, std::string name);
            AudioChannel(const AudioChannel& other);
            MANIFOLD_INLINE void addInputConnection(const Connection& connection) {
                m_inputConnections.push_back(connection);
            }
            MANIFOLD_INLINE std::vector<Connection>& getInputConnection() { return m_inputConnections; }
        private: 
            std::vector<Connection> m_inputConnections;
        };
    }
}