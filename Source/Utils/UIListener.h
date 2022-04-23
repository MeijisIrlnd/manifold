/*
  ==============================================================================

    UIListener.h
    Created: 22 Apr 2022 2:50:48am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <unordered_map>
#include <functional>
namespace Manifold
{
    enum class FUNCTION
    {
        TRANSPORT_PLAY,
        TRANSPORT_PAUSE,
        TRANSPORT_STOP
    };


    struct UIListener
    {
        std::unordered_map<FUNCTION, std::function<void(void)> > m_mappings;
        std::function<void(void)>& operator[](FUNCTION f) {
            if (m_mappings.find(f) != m_mappings.end()) {
                return m_mappings[f];
            }
        }

        std::function<void(void)>& at(FUNCTION f) {
            if (m_mappings.find(f) != m_mappings.end()) {
                return m_mappings[f];
            }
        }
    };
}