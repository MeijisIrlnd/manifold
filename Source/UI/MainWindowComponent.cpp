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
            m_playheadPositioner(m_engine.getPositionTracker())
        {
            setSize(400, 400);
            addAndMakeVisible(&m_transportComponent);
            addAndMakeVisible(&m_playheadPositioner);
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
            // Need the concept of a timescale here 
            m_playheadPositioner.setBounds(0, 0, getWidth(), getHeight());
            m_transportComponent.setBounds(0, getHeight() * 0.75, getWidth(), getHeight() * 0.25);
        }
    }

}

