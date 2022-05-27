/*
  ==============================================================================

    BaseWindow.h
    Created: 27 May 2022 2:01:37am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "WindowListener.h"
namespace Manifold
{
    namespace UI
    {
        enum class WINDOW_TYPE
        {
            PLUGIN, 
            SETTINGS
        };

        class BaseWindow : public juce::DocumentWindow
        {
        public: 
            BaseWindow(const juce::String& name, juce::Colour backgroundColour, int opts, WINDOW_TYPE t, WindowListener* listener) : 
                juce::DocumentWindow(name, backgroundColour, opts),
                m_type(t),
                m_listener(listener)
            {
            }

        protected: 
            WINDOW_TYPE m_type;
            WindowListener* m_listener{ nullptr };
        };
    }
}