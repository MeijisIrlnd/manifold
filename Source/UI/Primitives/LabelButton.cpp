/*
  ==============================================================================

    LabelButton.cpp
    Created: 17 May 2022 12:42:13am
    Author:  Syl

  ==============================================================================
*/

#include "LabelButton.h"
namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            LabelButton::LabelButton(const std::string& text)
            {
                m_label.setText(text, juce::dontSendNotification);
                addAndMakeVisible(&m_label);
                m_label.setInterceptsMouseClicks(false, false);
            }

            void LabelButton::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
            {
                if (m_listener != nullptr) {
                    m_listener->labelButtonClicked(this);
                }
            }

            void LabelButton::paint(juce::Graphics& g)
            {
                g.fillAll(juce::Colours::black);
            }

            void LabelButton::resized()
            {
                m_label.setBounds(getLocalBounds());
            }
        }
    }
}
