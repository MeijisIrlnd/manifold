/*
  ==============================================================================

    TopMenuBar.cpp
    Created: 17 May 2022 12:15:49am
    Author:  Syl

  ==============================================================================
*/

#include "TopMenuBar.h"

namespace Manifold
{
    namespace UI
    {
        TopMenuBar::TopMenuBar() : 
            m_fileButton("File"),
            m_editButton("Edit")
        {
            addAndMakeVisible(&m_fileButton);
            m_fileButton.addListener(this);
            addAndMakeVisible(&m_editButton);
        }

        TopMenuBar::~TopMenuBar()
        {
        }

        void TopMenuBar::labelButtonClicked(Primitives::LabelButton* b)
        {
            if (b == &m_fileButton) {
                juce::PopupMenu popup;
                popup.addItem(1, "Save");
                popup.addItem(2, "Save As");
                popup.addItem(3, "SETTINGS");
                popup.showMenuAsync(juce::PopupMenu::Options(), [this](int res) {
                    FILE_MENU_OPTS selection = static_cast<FILE_MENU_OPTS>(res);
                    switch (selection)
                    {
                        case FILE_MENU_OPTS::SAVE: 
                        {
                            break;
                        }

                        case FILE_MENU_OPTS::SAVE_AS: 
                        {
                            break;
                        }

                        case FILE_MENU_OPTS::SETTINGS:
                        {
                            // Show a device manager (in a popup?) 
                            // Call back to MainWindowComponent
                            GET_WINDOW_MANAGER()->addSettingsWindow();
                            break;
                        }

                        default: 
                        {
                            break;
                        }
                    } 
                });
            }
        }

        void TopMenuBar::paint(MANIFOLD_UNUSED juce::Graphics& g)
        {
        }
        void TopMenuBar::resized()
        {
            auto w = getWidth() / 32;
            m_fileButton.setBounds(0, 0, w, getHeight());
            m_editButton.setBounds(w, 0, w, getHeight());
        }
    }
}