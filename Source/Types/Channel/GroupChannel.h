/*
  ==============================================================================

    GroupChannel.h
    Created: 12 Jun 2022 7:06:03pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "InternalChannel.h"
namespace Manifold::Audio
{
    using Connection = juce::AudioProcessorGraph::Connection;
    class GroupChannel : public InternalChannel
    {
    public: 
        GroupChannel(int internalId, std::string name);
        GroupChannel(const GroupChannel& other);

        MANIFOLD_INLINE bool checkIfChannelIsInput(const int id) {
            return m_inputConnections.find(id) != m_inputConnections.end();
        }

        MANIFOLD_INLINE void addInputConnection(const int channel, const Connection& toAdd) {
            if (m_inputConnections.find(channel) != m_inputConnections.end()) {
                m_inputConnections.at(channel).push_back(toAdd);
            }
            else {
                std::vector<Connection> temp = { toAdd };
                m_inputConnections.emplace(channel, std::move(temp));
            }

        }

        MANIFOLD_INLINE void removeInputConnectionsForChannel(const int channel) {
            auto it = m_inputConnections.find(channel);
            m_inputConnections.erase(it);
        }

    private: 
        std::unordered_map<int, std::vector<Connection>> m_inputConnections;
        
    }; 

}