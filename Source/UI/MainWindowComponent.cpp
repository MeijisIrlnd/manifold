/*
  ==============================================================================

    MainWindowComponent.cpp
    Created: 22 Apr 2022 1:37:01am
    Author:  Syl

  ==============================================================================
*/

#include "MainWindowComponent.h"

namespace Manifold
{
    namespace UI
    {
        MainWindowComponent::MainWindowComponent(UIListener* uiListener) :
            m_transportComponent(uiListener)
        {
            setSize(400, 400);
            addAndMakeVisible(&m_transportComponent);
        }

        MainWindowComponent::~MainWindowComponent()
        {
        }

        void MainWindowComponent::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::black);
            g.fillAll();
        }

        void MainWindowComponent::resized()
        {
            m_transportComponent.setBounds(0, getHeight() * 0.75, getWidth(), getHeight() * 0.25);
        }
    }

}

