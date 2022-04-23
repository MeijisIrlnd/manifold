/*
  ==============================================================================

    SVGButton.cpp
    Created: 22 Apr 2022 2:24:24am
    Author:  Syl

  ==============================================================================
*/

#include "SVGButton.h"

namespace Manifold
{
    namespace UI
    {
        namespace Primitives
        {
            SVGButton::SVGButton(const void* imageData, int size)
            {
                m_icon = juce::Drawable::createFromImageData(imageData, size);
                m_icon->setInterceptsMouseClicks(false, false);
                m_icon->replaceColour(juce::Colours::white, juce::Colours::black);
            }

            SVGButton::~SVGButton()
            {
            }

            const int SVGButton::getClickCount() const {
                return m_clickCount;
            }

            void SVGButton::mouseUp(const juce::MouseEvent& ev)
            {
                ++m_clickCount;
                if (m_listener != nullptr) {
                    m_listener->svgButtonClicked(this);
                }
            }

            void SVGButton::paint(juce::Graphics& g)
            {
                juce::Rectangle<float> local(getX(), getY(), getWidth(), getHeight());
                m_icon->setTransformToFit(local, juce::RectanglePlacement::centred);
                m_icon->draw(g, 1);
            }

            void SVGButton::resized()
            {
            }

        }
    }
}
