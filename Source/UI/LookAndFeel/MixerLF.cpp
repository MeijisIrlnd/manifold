/*
  ==============================================================================

    MixerLF.cpp
    Created: 7 May 2022 7:00:11pm
    Author:  Syl

  ==============================================================================
*/

#include "MixerLF.h"

namespace Manifold
{
    namespace UI
    {
        juce::Font MixerLF::m_labelFont = juce::Typeface::createSystemTypefaceFor(BinaryData::PixelTandysoft0rJG_ttf, BinaryData::PixelTandysoft0rJG_ttfSize);
        
        MixerLF::MixerLF()
        {
            m_vThumb = juce::ImageCache::getFromMemory(BinaryData::MixerHandle_png, BinaryData::MixerHandle_pngSize);
            m_rThumb = juce::ImageCache::getFromMemory(BinaryData::RotaryHandle_png, BinaryData::RotaryHandle_pngSize);
            setColour(juce::TextEditor::backgroundColourId, juce::Colours::transparentWhite);
            setColour(juce::TextEditor::textColourId, juce::Colours::white);
            setColour(juce::TextEditor::outlineColourId, juce::Colours::transparentWhite);
            //m_labelFont = juce::Typeface::createSystemTypefaceFor(BinaryData::PixelTandysoft0rJG_ttf, BinaryData::PixelTandysoft0rJG_ttfSize);
        }

        void MixerLF::drawLinearSlider(juce::Graphics& g, int x, int y, int width, int height,
            float sliderPos,
            float minSliderPos,
            float maxSliderPos,
            const juce::Slider::SliderStyle style, juce::Slider& slider)
        {
            using namespace juce;
            if (slider.isBar())
            {
                g.setColour(slider.findColour(Slider::trackColourId));
                g.fillRect(slider.isHorizontal() ? Rectangle<float>(static_cast<float> (x), (float)y + 0.5f, sliderPos - (float)x, (float)height - 1.0f)
                    : Rectangle<float>((float)x + 0.5f, sliderPos, (float)width - 1.0f, (float)y + ((float)height - sliderPos)));
            }
            else
            {
                auto thumbWidth = width / 4;
                auto thumbHeight = height / 6;
                int yOffset = thumbHeight / 2;
                maxSliderPos += yOffset;
                minSliderPos -= yOffset;
                auto isTwoVal = (style == Slider::SliderStyle::TwoValueVertical || style == Slider::SliderStyle::TwoValueHorizontal);
                auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

                auto trackWidth = jmin(6.0f, slider.isHorizontal() ? (float)height * 0.25f : (float)width * 0.25f);

                Point<float> startPoint(slider.isHorizontal() ? (float)x : (float)x + (float)width * 0.5f,
                    slider.isHorizontal() ? (float)y + (float)height * 0.5f : (float)(height + y - yOffset));

                Point<float> endPoint(slider.isHorizontal() ? (float)(width + x) : startPoint.x,
                    slider.isHorizontal() ? startPoint.y : (float)y + (yOffset));

                Path backgroundTrack;
                backgroundTrack.startNewSubPath(startPoint);
                backgroundTrack.lineTo(endPoint);
                g.setColour(slider.findColour(Slider::backgroundColourId));
                g.strokePath(backgroundTrack, { trackWidth, PathStrokeType::curved, PathStrokeType::rounded });

                Path valueTrack;
                Point<float> minPoint, maxPoint, thumbPoint;

                if (isTwoVal || isThreeVal)
                {
                    minPoint = { slider.isHorizontal() ? minSliderPos : (float)width * 0.5f,
                                 slider.isHorizontal() ? (float)height * 0.5f : minSliderPos };

                    if (isThreeVal)
                        thumbPoint = { slider.isHorizontal() ? sliderPos : (float)width * 0.5f,
                                       slider.isHorizontal() ? (float)height * 0.5f : sliderPos };

                    maxPoint = { slider.isHorizontal() ? maxSliderPos : (float)width * 0.5f,
                                 slider.isHorizontal() ? (float)height * 0.5f : maxSliderPos };
                }
                else
                {
                    auto kx = slider.isHorizontal() ? sliderPos : ((float)x + (float)width * 0.5f);
                    auto ky = slider.isHorizontal() ? ((float)y + (float)height * 0.5f) : sliderPos;

                    minPoint = startPoint;
                    maxPoint = { kx, ky };
                }

                //auto thumbWidth = getSliderThumbRadius(slider);


                if (!isTwoVal)
                {
                    //g.setColour(slider.findColour(Slider::thumbColourId));
                    auto thumbY = juce::jmin(static_cast<float>(height - yOffset), maxPoint.getY() - yOffset);
                    thumbY = juce::jmax(static_cast<float>(endPoint.getY() - yOffset), thumbY - yOffset);
                    juce::Rectangle<float> targetRect((width / 2.0f) - (thumbWidth / 2.0f), thumbY, static_cast<float> (thumbWidth), static_cast<float> (thumbHeight));
                    g.setImageResamplingQuality(juce::Graphics::ResamplingQuality::highResamplingQuality);
                    g.drawImage(m_vThumb, targetRect);
                    //g.setColour(juce::Colours::red);
                    //g.fillEllipse(Rectangle<float>(static_cast<float> (thumbWidth), static_cast<float> (thumbWidth)).withCentre(isThreeVal ? thumbPoint : maxPoint));
                }

                if (isTwoVal || isThreeVal)
                {
                    auto sr = jmin(trackWidth, (slider.isHorizontal() ? (float)height : (float)width) * 0.4f);
                    auto pointerColour = slider.findColour(Slider::thumbColourId);

                    if (slider.isHorizontal())
                    {
                        drawPointer(g, minSliderPos - sr,
                            jmax(0.0f, (float)y + (float)height * 0.5f - trackWidth * 2.0f),
                            trackWidth * 2.0f, pointerColour, 2);

                        drawPointer(g, maxSliderPos - trackWidth,
                            jmin((float)(y + height) - trackWidth * 2.0f, (float)y + (float)height * 0.5f),
                            trackWidth * 2.0f, pointerColour, 4);
                    }
                    else
                    {
                        //drawPointer(g, jmax(0.0f, (float)x + (float)width * 0.5f - trackWidth * 2.0f),
                        //    minSliderPos - trackWidth,
                        //    trackWidth * 2.0f, pointerColour, 1);
                        //
                        //drawPointer(g, jmin((float)(x + width) - trackWidth * 2.0f, (float)x + (float)width * 0.5f), maxSliderPos - sr,
                        //    trackWidth * 2.0f, pointerColour, 3);
                    }
                }
            }
        }
            void MixerLF::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
            {
                using namespace juce;
                auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
                auto fill = slider.findColour(Slider::rotarySliderFillColourId);

                auto bounds = Rectangle<int>(x, y, width, height).toFloat().reduced(10);

                auto radius = jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;
                MANIFOLD_UNUSED auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
                auto lineW = jmin(8.0f, radius * 0.5f);
                auto arcRadius = radius - lineW * 0.5f;

                Path backgroundArc;
                backgroundArc.addCentredArc(bounds.getCentreX(),
                    bounds.getCentreY(),
                    arcRadius,
                    arcRadius,
                    0.0f,
                    rotaryStartAngle,
                    rotaryEndAngle,
                    true);

                g.setColour(outline);
                g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));
                juce::AffineTransform rotation = juce::AffineTransform::rotation(toAngle, width / 2.0f, height / 2.0f);
                m_rThumb = m_rThumb.rescaled(width, height, juce::Graphics::ResamplingQuality::highResamplingQuality);
                g.drawImageTransformed(m_rThumb, rotation);
            }
    }
}