/*
  ==============================================================================

    CacheTester.h
    Created: 23 Aug 2022 12:36:38am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "../Utils/AudioCache.h"
namespace Manifold
{
    namespace Testing
    {
        static void testCache()
        {
            juce::AudioFormatManager fmtManager;
            fmtManager.registerBasicFormats();
            juce::File testFile("C:\\Users\\Syl\\Music\\rocks rock - henrys first rap album please dont pirate thanks for listening fixed the tracks\\Rocks Rock EP\\2 - Rocks Rock!.mp3");
            DBG("Adding to cache");
            Audio::CachedAudioFile::Ptr cached = Audio::AudioCache::addToCache(testFile);
            Audio::CachedAudioFile::Ptr fromMemory = Audio::AudioCache::getFromCache(testFile);
            Audio::CachedAudioFile::Ptr fromMemory2 = Audio::AudioCache::getFromCache(testFile);
            DBG(fromMemory->getReferenceCount());
        }
    }   
}