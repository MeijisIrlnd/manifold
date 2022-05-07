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
#include "../Macros.h"
namespace Manifold
{
    enum class FUNCTION
    {
        TRANSPORT_PLAY,
        TRANSPORT_PAUSE,
        TRANSPORT_STOP
    };

    enum class CHANGE_TYPE
    {
        CHANGE_POSITION,
        CHANGE_BPM,
        CHANGE_TIMESIG
    };

    struct UIListener
    {
        std::unordered_map<FUNCTION, std::function<void(void)> > m_mappings;
        MANIFOLD_INLINE std::function<void(void)>& operator[](FUNCTION f) {
            return at(f);
        }

        std::function<void(void)>& at(FUNCTION f) {
            return m_mappings[f];
        }
    };
}