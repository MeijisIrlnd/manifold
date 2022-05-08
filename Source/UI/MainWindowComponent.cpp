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
            setSize(1920, 1080);
            setWantsKeyboardFocus(true);
            addAndMakeVisible(&m_transportComponent);
            addAndMakeVisible(&m_arrangementView);
            m_arrangementView.setVisible(false);
            addAndMakeVisible(&m_mixerView);
            addKeyListener(this);
        }

        MainWindowComponent::~MainWindowComponent()
        {
        }

        bool MainWindowComponent::keyPressed(const juce::KeyPress& key, MANIFOLD_UNUSED juce::Component* fromComponent)
        {
            if (key.isKeyCode(juce::KeyPress::tabKey)) {
                m_mixerView.setVisible(!m_mixerView.isVisible());
                m_arrangementView.setVisible(!m_arrangementView.isVisible());
            }
            return true;
        }

        void MainWindowComponent::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::white);
            g.fillAll();
        }

        void MainWindowComponent::resized()
        {
            m_transportComponent.setBounds(getWidth() / 4, static_cast<int>(getHeight() * 0.95), getWidth() / 2, static_cast<int>(getHeight() * 0.05));
            m_arrangementView.setBounds(0, 0, getWidth(), static_cast<int>(getHeight() * 0.75));
            m_mixerView.setBounds(0, 0, getWidth(), static_cast<int>(getHeight() * 0.9));
        }
    }

}

