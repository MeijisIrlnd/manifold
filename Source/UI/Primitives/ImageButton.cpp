/*
  ==============================================================================

    ImageButton.cpp
    Created: 7 May 2022 10:56:12pm
    Author:  Syl

  ==============================================================================
*/

#include "ImageButton.h"

namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            ImageButton::ImageButton(const char* image, const int imageSize)
            {
                m_image = juce::ImageCache::getFromMemory(image, imageSize);
            }

            void ImageButton::paint(MANIFOLD_UNUSED juce::Graphics& g)
            {
                juce::Rectangle<float> bounds(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
                g.drawImage(m_image, bounds);
            }

            void ImageButton::resized()
            {
            }

            void ImageToggleButton::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
            {
                m_state = !m_state;
                if (m_listener != nullptr) {
                    m_listener->imageToggleButtonClicked(this, m_state);
                }
                repaint();
            }

            ImageToggleButton::ImageToggleButton(const char* offImage, const int offImageSize, const char* onImage, const int onImageSize)
            {
                m_offImage = juce::ImageCache::getFromMemory(offImage, offImageSize);
                m_onImage = juce::ImageCache::getFromMemory(onImage, onImageSize);
            }

            void ImageToggleButton::paint(juce::Graphics& g)
            {
                juce::Image& toDraw = m_state ? m_onImage : m_offImage;
                juce::Rectangle<float> bounds(0, 0, static_cast<float>(getWidth()), static_cast<float>(getHeight()));
                g.drawImage(toDraw, bounds);
            }

            void ImageToggleButton::resized()
            {
            }
        }
    }
}