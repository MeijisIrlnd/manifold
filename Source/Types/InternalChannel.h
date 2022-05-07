/*
  ==============================================================================

    Channel.h
    Created: 24 Apr 2022 9:25:47pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
namespace Manifold
{
    namespace Audio
    {
        class InternalChannel
        {
        public: 
            InternalChannel(int internalId, std::string name);
            InternalChannel(const InternalChannel& other);
            void rename(const std::string& newName);
            MANIFOLD_INLINE const std::string& getName() const { return m_name; }
            MANIFOLD_INLINE void setVolume(double newVolume) { m_channelVolume = newVolume; }
            MANIFOLD_INLINE double getVolume() const { return m_channelVolume; }
            MANIFOLD_INLINE void setPan(double newPan) { m_channelPan = newPan; }
            MANIFOLD_INLINE double getPan() const { return m_channelPan; }
            MANIFOLD_INLINE void setMuteState(bool state) { m_muteState = state; }
            MANIFOLD_INLINE bool getMuteState() const { return m_muteState; }
            MANIFOLD_INLINE void setSoloState(bool state) { m_soloState = state; }
            MANIFOLD_INLINE bool getSoloState() const { return m_soloState; }
            MANIFOLD_INLINE void setColour(juce::Colour& c) { m_colour = c; }
            MANIFOLD_INLINE juce::Colour& getColour() { return m_colour; }
        private: 
            std::string m_name;
            const int m_internalId;
            double m_channelVolume{ 1 };
            double m_channelPan{ 0.5 };
            bool m_muteState{ false };
            bool m_soloState{ false };
            juce::Colour m_colour{ 0xFFF5F5DC };
        };
    }
}