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
            auto screenSize = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay()->userArea;
            setSize(screenSize.getWidth(), screenSize.getHeight());
            //setSize(1920, 1080);
            // Initialise baby.. 
            GET_WINDOW_MANAGER();
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
            addAndMakeVisible(&m_menuBar);
            addKeyListener(this);
            GET_ENGINE()->addListener(this);
        }

        MainWindowComponent::~MainWindowComponent()
        {
            setLookAndFeel(nullptr);
            WindowManager::shutdown();
        }

        bool MainWindowComponent::keyPressed(const juce::KeyPress& key, MANIFOLD_UNUSED juce::Component* fromComponent)
        {
            if (key.isKeyCode(juce::KeyPress::tabKey)) {
                m_mixerView.setVisible(!m_mixerView.isVisible());
                m_mixerScrollbar.setVisible(!m_mixerScrollbar.isVisible());
                m_arrangementView.setVisible(!m_arrangementView.isVisible());
            }
            else if (key.isKeyCode(78) && (key.getModifiers().isShiftDown() && key.getModifiers().isCtrlDown())) {
                DBG("CTRL + SHIFT + N");
                // Show context menu
                juce::PopupMenu popup;
                popup.addItem(1, "Create audio channel");
                popup.addItem(2, "Create midi channel");
                popup.addItem(3, "Create bus channel");

                popup.showMenuAsync(juce::PopupMenu::Options(), [this](int res) {
                    switch (res) {
                    case 1:
                    {
                        GET_ENGINE()->createChannel(AUDIO_CHANNEL);
                        break;
                    }
                    case 2:
                    {
                        juce::KnownPluginList& vstList = GET_ENGINE()->getPluginList();
                        juce::Array<juce::PluginDescription> descs = GET_ENGINE()->getFilteredDescriptions(true);
                        std::function<void(int)> userCallback = [this, descs](int result) {
                            juce::KnownPluginList& vstList = GET_ENGINE()->getPluginList();
                            auto chosenIndex = vstList.getIndexChosenByMenu(descs, result);
                            if (chosenIndex == -1) { return; }
                            auto selected = descs[chosenIndex];
                            GET_ENGINE()->createChannel(MIDI_CHANNEL, selected);
                        };
                        juce::PopupMenu vstMenu;

                        vstList.addToMenu(vstMenu, descs, juce::KnownPluginList::sortAlphabetically);
                        vstMenu.showMenuAsync(juce::PopupMenu::Options(), userCallback);
                        break;
                    }
                    case 3: 
                    {
                        GET_ENGINE()->createChannel(GROUP_CHANNEL);
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                    });
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
            int menuHeight = getHeight() / 32;
            m_transportComponent.setBounds(getWidth() / 4, static_cast<int>(getHeight() * 0.95), getWidth() / 2, static_cast<int>(getHeight() * 0.05));
            m_menuBar.setBounds(0, 0, getWidth(), menuHeight);
            m_arrangementView.setBounds(0, menuHeight, getWidth(), static_cast<int>(getHeight() * 0.75) - menuHeight);
            // So mixerChannel width = getWidth() / 16
            // min width is get width, but as channels are added, add getWidth() / 16 ONCE channelWIdth * numChannels > width
            auto viewWidth = m_mixerView.getNumChannels() * (getWidth() / 16);
            viewWidth = juce::jmax<int>(viewWidth, getWidth());
            // The THING is getWidth() / 16 needs to get passed to the mixer view somehow..
            m_mixerView.setBounds(0, menuHeight, viewWidth, static_cast<int>(getHeight() * 0.9) - menuHeight);
            m_mixerScrollbar.setBounds(0, menuHeight, getWidth(), static_cast<int>(getHeight() * 0.9) - menuHeight);

        }
    }

}

