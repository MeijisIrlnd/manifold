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
            m_transportComponent(uiListener),
            m_mixerView(m_mixerChannelWidth)
        {
            setSize(1920, 1080);
            setLookAndFeel(&m_overallLF);
            setWantsKeyboardFocus(true);
            addAndMakeVisible(&m_transportComponent);
            addAndMakeVisible(&m_arrangementView);
            m_arrangementView.setVisible(false);
            addAndMakeVisible(&m_mixerView);
            m_mixerScrollbar.setViewedComponent(&m_mixerView, false);
            m_mixerScrollbar.setScrollBarsShown(false, true, false, false);
            m_mixerScrollbar.setScrollBarThickness(30);
            addAndMakeVisible(&m_mixerScrollbar);
            addKeyListener(this);
            GET_ENGINE->addListener(this);
        }

        MainWindowComponent::~MainWindowComponent()
        {
            setLookAndFeel(nullptr);
        }

        void MainWindowComponent::onPluginUIOpened(juce::AudioProcessor* processor)
        {
            m_pluginWindowManager.addWindow(processor);
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
            m_mixerChannelWidth = getWidth() / 16;
            m_transportComponent.setBounds(getWidth() / 4, static_cast<int>(getHeight() * 0.95), getWidth() / 2, static_cast<int>(getHeight() * 0.05));
            m_arrangementView.setBounds(0, 0, getWidth(), static_cast<int>(getHeight() * 0.75));
            // So mixerChannel width = getWidth() / 16
            // min width is get width, but as channels are added, add getWidth() / 16 ONCE channelWIdth * numChannels > width
            auto viewWidth = m_mixerView.getNumChannels() * (getWidth() / 16);
            viewWidth = juce::jmax<int>(viewWidth, getWidth());
            // The THING is getWidth() / 16 needs to get passed to the mixer view somehow..
            m_mixerView.setBounds(0, 0, viewWidth, static_cast<int>(getHeight() * 0.9));
            m_mixerScrollbar.setBounds(0, 0, getWidth(), static_cast<int>(getHeight() * 0.9));

        }
    }

}

