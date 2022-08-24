/*
  ==============================================================================

    ColourPicker.cpp
    Created: 8 May 2022 12:06:24am
    Author:  Syl

  ==============================================================================
*/

#include "ColourPicker.h"

namespace Manifold
{
    namespace UI
    {
        ColourPicker::ColourPicker(Manifold::Audio::InternalChannel* associatedChannel) : 
            m_channel(associatedChannel)
        {
            for (auto i = 0; i < 5; i++) {
                std::unique_ptr<ColourPickerMenuItem> current(new ColourPickerMenuItem(juce::Colour(m_availableColours[i])));
                m_popup.addCustomItem(i + 1, std::move(current), nullptr);
            }
            m_icon = juce::ImageCache::getFromMemory(BinaryData::ColourPickerIcon_png, BinaryData::ColourPickerIcon_pngSize);
        }

        void ColourPicker::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
        {
            std::function<void(int)> popupCallback = [this](int res) {
                if (res != 0) {
                    juce::Colour newColour(m_availableColours[res - 1]);
                    if (m_listener != nullptr) {
                        m_listener->onColourPicked(newColour);
                    }
                }
            };

            juce::PopupMenu::Options opts;
            m_popup.showMenuAsync(opts, popupCallback);
        }

        void ColourPicker::paint(juce::Graphics& g)
        {
            m_icon = m_icon.rescaled(getWidth(), getHeight(), juce::Graphics::ResamplingQuality::highResamplingQuality);
            g.drawImageAt(m_icon, 0, 0, false);
        }

        void ColourPicker::resized()
        {
        }

    }
}

