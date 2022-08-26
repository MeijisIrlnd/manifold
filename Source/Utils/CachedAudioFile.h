/*
  ==============================================================================

    CachedAudioFile.h
    Created: 22 Aug 2022 11:38:33pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
namespace Manifold::Audio
{
    class CachedAudioFile : public juce::ReferenceCountedObject
    {
    public: 
        using Ptr = juce::ReferenceCountedObjectPtr<CachedAudioFile>;
        CachedAudioFile(const juce::File& associated_, juce::int64 hash_, const juce::AudioBuffer<float>& buffer_, double originalSampleRate_);
        ~CachedAudioFile();
        juce::File associatedFile;
        juce::int64 hash;
        juce::AudioBuffer<float> buffer;
        double originalSampleRate;
    };
}