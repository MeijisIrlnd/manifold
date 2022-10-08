/*
  ==============================================================================

    SampleBrowser.cpp
    Created: 1 Oct 2022 3:18:14am
    Author:  Syl

  ==============================================================================
*/

#include "SampleBrowserComponent.h"

namespace Manifold::UI
{
    SampleBrowserComponent::SampleBrowserComponent() : m_fileFilter(".wav;*.mp3", "", ""),
        m_contentsList(&m_fileFilter, m_directoryParseThread),
        m_fileTreeComponent(m_contentsList)
    {
        m_contentsList.setDirectory(juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory), true, true);
        addAndMakeVisible(&m_fileTreeComponent);
    }

    SampleBrowserComponent::~SampleBrowserComponent()
    {
    }

    void SampleBrowserComponent::paint(MANIFOLD_UNUSED juce::Graphics& g)
    {
    }

    void SampleBrowserComponent::resized()
    {
        m_fileTreeComponent.setBounds(getLocalBounds());
    }
}