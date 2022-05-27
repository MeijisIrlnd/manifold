/*
  ==============================================================================

    TopMenuBar.h
    Created: 17 May 2022 12:15:49am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Windows/WindowManager.h"
#include "../../Primitives/LabelButton.h"
#include "../../Primitives/ImageButton.h"
namespace Manifold
{
    namespace UI
    {
        enum class FILE_MENU_OPTS
        {
            NONE,
            SAVE, 
            SAVE_AS, 
            SETTINGS
        };

        class TopMenuBar : public juce::Component, public Primitives::ButtonListener
        {
        public: 
            TopMenuBar();
            ~TopMenuBar() override;
            void labelButtonClicked(Primitives::LabelButton* b) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            Primitives::LabelButton m_fileButton, m_editButton;
            // Options and callbacks to them, so Preferences: function() 
        };
    }
}