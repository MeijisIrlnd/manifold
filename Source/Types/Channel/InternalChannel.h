/*
  ==============================================================================

    Channel.h
    Created: 24 Apr 2022 9:25:47pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Macros.h"
namespace Manifold
{
    namespace Audio
    {
        enum class CHANNEL_TYPE
        {
            AUDIO,
            MIDI,
            GROUP
        };

        using Connection = juce::AudioProcessorGraph::Connection;
        class InternalChannel
        {
        public: 
            InternalChannel(int internalId, std::string name, CHANNEL_TYPE channelType);
            InternalChannel(const InternalChannel& other);
            virtual ~InternalChannel();
            void rename(const std::string& newName);
            MANIFOLD_INLINE CHANNEL_TYPE getChannelType() const { return m_channelType; }
            MANIFOLD_INLINE const int getId() const { return m_internalId; }
            MANIFOLD_INLINE const std::string& getName() const { return m_name; }
            MANIFOLD_INLINE void addListener(juce::ValueTree::Listener* newListener) { m_valueTree.addListener(newListener); }
            MANIFOLD_INLINE juce::Value getParamAsValue(juce::Identifier param) { return m_valueTree.getPropertyAsValue(param, nullptr); }
            MANIFOLD_INLINE void setColour(juce::Colour& c) { m_colour = c; }
            MANIFOLD_INLINE juce::Colour& getColour() { return m_colour; }
            MANIFOLD_INLINE void setHasRenamed(bool newState) { m_hasRenamed = newState; }
            MANIFOLD_INLINE bool getHasRenamed() const { return m_hasRenamed; }
            MANIFOLD_INLINE std::vector<Connection>& getSendConnections() { return m_sendConnections; }
            MANIFOLD_INLINE void addSendConnection(const Connection& connection) { m_sendConnections.push_back(connection); }
            MANIFOLD_INLINE std::vector<Connection>& getOutputConnections() { return m_outputConnections; }
            MANIFOLD_INLINE void addOutputConnection(const Connection& connection) {
                m_outputConnections.push_back(connection);
            }
        protected: 
            CHANNEL_TYPE m_channelType;
            std::string m_name;
            bool m_hasRenamed{ true };
            const int m_internalId;
            juce::ValueTree m_valueTree;
            juce::Colour m_colour{ 0xFFF5F5DC };
            std::vector<Connection> m_sendConnections;
            std::vector<Connection> m_outputConnections;
        };
    }
}