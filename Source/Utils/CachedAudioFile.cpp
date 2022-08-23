/*
  ==============================================================================

    CachedAudioFile.cpp
    Created: 22 Aug 2022 11:59:50pm
    Author:  Syl

  ==============================================================================
*/

#include "CachedAudioFile.h"
#include "AudioCache.h"
namespace Manifold::Audio
{

    CachedAudioFile::CachedAudioFile(const juce::File& associated_, juce::int64 hash_, const juce::AudioBuffer<float>& buffer_) : 
        associatedFile(associated_), hash(hash_), buffer(buffer_)
    {
    }

    CachedAudioFile::~CachedAudioFile()
    {
        //AudioCache::removeFromCache(hash);
    }
}