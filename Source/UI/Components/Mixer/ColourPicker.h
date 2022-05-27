/*
  ==============================================================================

    ColourPicker.h
    Created: 8 May 2022 12:06:23am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <inttypes.h>
#include "../../../Macros.h"
#include "../../../Types/Channel/InternalChannel.h"
#include "ColourPickerMenuItem.h"
namespace Manifold
{
    namespace UI
    {
        struct ColourPickerListener
        {
            virtual ~ColourPickerListener() {}
            virtual void onColourPicked(juce::Colour& newColour) = 0;
        };

        class ColourPicker : public juce::Component
        {
        public: 
            ColourPicker(Manifold::Audio::InternalChannel* associatedChannel);
            MANIFOLD_INLINE void addListener(ColourPickerListener* newListener) { m_listener = newListener; }
            void mouseUp(const juce::MouseEvent& ev) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            Manifold::Audio::InternalChannel* m_channel{ nullptr };
            const uint32_t m_availableColours[5] = {
                0xFFF5F5DC,
                0xFF1C2541,
                0XFFEF626C,
                0xFF519E8A,
                0xFF8A95a5
            };

            juce::PopupMenu m_popup;
            ColourPickerListener* m_listener{ nullptr };
        };
    }
}