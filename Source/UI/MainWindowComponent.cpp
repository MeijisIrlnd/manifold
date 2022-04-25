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
        MainWindowComponent::MainWindowComponent(UIListener* uiListener, Manifold::Audio::ManifoldEngine& engine) :
            m_transportComponent(uiListener),
            m_engine(engine),
            m_arrangementView(engine)
        {
            setSize(1920, 1080);
            addAndMakeVisible(&m_transportComponent);
            addAndMakeVisible(&m_arrangementView);
        }

        MainWindowComponent::~MainWindowComponent()
        {
        }

        void MainWindowComponent::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::white);
            g.fillAll();
        }

        void MainWindowComponent::resized()
        {
            m_transportComponent.setBounds(getWidth() / 4, getHeight() * 0.95, getWidth() / 2, getHeight() * 0.05);
            m_arrangementView.setBounds(0, 0, getWidth(), getHeight() * 0.75);
        }
    }

}

