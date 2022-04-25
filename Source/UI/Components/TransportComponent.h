/*
  ==============================================================================

    TransportComponent.h
    Created: 22 Apr 2022 2:11:41am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Primitives/SVGButton.h"
#include "../../Utils/UIListener.h"
using namespace Manifold::UI::Primitives;
namespace Manifold
{
    namespace UI
    {
        class TransportComponent : public juce::Component,
            public ButtonListener
        {
        public: 
            TransportComponent(UIListener* uiListener);
            ~TransportComponent() override;
            void svgButtonClicked(SVGButton* b) override;
            void paint(juce::Graphics& g) override; 
            void resized() override;
        private: 
            UIListener* m_uiListener;
            SVGButton m_playPauseButton, m_stopButton;
            juce::TextEditor m_bpmInputField;
        };
    }
}