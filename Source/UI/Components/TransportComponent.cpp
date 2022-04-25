/*
  ==============================================================================

    TransportComponent.cpp
    Created: 22 Apr 2022 2:11:41am
    Author:  Syl

  ==============================================================================
*/

#include "TransportComponent.h"

namespace Manifold
{
    namespace UI
    {
        TransportComponent::TransportComponent(UIListener* uiListener) :
            m_playPauseButton(BinaryData::Play_svg, BinaryData::Play_svgSize),
            m_stopButton(BinaryData::Stop_svg, BinaryData::Stop_svgSize),
            m_uiListener(uiListener)
        {
            addAndMakeVisible(&m_playPauseButton);
            addAndMakeVisible(&m_stopButton);
            m_bpmInputField.setText("120", false);
            addAndMakeVisible(&m_bpmInputField);
            m_playPauseButton.addListener(this);
            m_stopButton.addListener(this);
        }

        TransportComponent::~TransportComponent()
        {
        }

        void TransportComponent::svgButtonClicked(SVGButton* b)
        {
            if (b == &m_playPauseButton) {
                auto clickCount = m_playPauseButton.getClickCount();
                if (clickCount % 2 == 1) {
                    m_uiListener->at(Manifold::FUNCTION::TRANSPORT_PLAY)();
                }
                else {
                    m_uiListener->at(Manifold::FUNCTION::TRANSPORT_PAUSE)();
                }
            }
            else if (b == &m_stopButton) {
                m_uiListener->operator[](Manifold::FUNCTION::TRANSPORT_STOP)();
            }
        }

        void TransportComponent::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::lightcoral);
            g.fillAll();
        }

        void TransportComponent::resized()
        {
            m_playPauseButton.setBounds(0, 0, getWidth() / 4, getHeight());
            m_stopButton.setBounds(getWidth() / 4, 0, getWidth() / 4, getHeight());
            m_bpmInputField.setBounds(getWidth() / 2, 0, getWidth() / 4, getHeight());
        }
    }
}