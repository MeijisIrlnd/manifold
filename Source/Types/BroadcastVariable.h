/*
  ==============================================================================

    BroadcastVariable.h
    Created: 25 Apr 2022 1:47:36am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//namespace Manifold
//{
//    template <typename T>
//    struct BroadcastVariable : public juce::ChangeBroadcaster
//    {
//        BroadcastVariable<T>() { }
//        BroadcastVariable<T>(const BroadcastVariable<T>& other) { m_value = other.value; }
//        BroadcastVariable<T>(T& value) : m_value(value) { }
//
//        void operator=(T& newValue) { m_value = newValue; }
//
//        T& get() { return m_value; }
//    private: 
//        T m_value;
//    };
//}