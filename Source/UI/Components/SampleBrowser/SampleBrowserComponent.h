/*
  ==============================================================================

    SampleBrowser.h
    Created: 1 Oct 2022 3:18:14am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <Macros.h>
namespace Manifold::UI
{
    class SampleBrowserComponent : public juce::Component
    {
    public:
        SampleBrowserComponent();
        ~SampleBrowserComponent() override;
        void paint(juce::Graphics& g) override;
        void resized() override;
    private: 
        juce::WildcardFileFilter m_fileFilter;
        juce::FileTreeComponent m_fileTreeComponent;
        juce::DirectoryContentsList m_contentsList;
        juce::TimeSliceThread m_directoryParseThread{ "Directory Parse" };
    };
}