/*
  ==============================================================================

    Macros.h
    Created: 22 Apr 2022 1:58:36am
    Author:  Syl

  ==============================================================================
*/

#pragma once

#ifndef MANIFOLD_INLINE
    #ifdef _MSC_VER 
        #define MANIFOLD_INLINE forcedinline 
    #else 
        #define MANIFOLD_INLINE __attribute__((alwaysinline))
    #endif
#endif

#ifndef MANIFOLD_UNUSED 
#define MANIFOLD_UNUSED [[maybe_unused]]
#endif

#ifndef MANIFOLD_LIKELY 
    #define MANIFOLD_LIKELY [[likely]]
#endif

#ifndef MANIFOLD_UNLIKELY 
    #define MANIFOLD_UNLIKELY [[unlikely]]
#endif 

#ifndef GET_ENGINE
#define GET_ENGINE() Manifold::Audio::ManifoldEngine::getInstance()
#endif

#ifndef GET_ZOOM_MANAGER
    #define GET_ZOOM_MANAGER() Manifold::ZoomManager::getInstance()
#endif

#ifndef GET_POSITION_TRACKER 
#define GET_POSITION_TRACKER() Manifold::Audio::Core::PositionTracker::getInstance()
#endif 

#ifndef AUDIO_CHANNEL
#define AUDIO_CHANNEL Manifold::Audio::CHANNEL_TYPE::AUDIO
#endif 

#ifndef MIDI_CHANNEL 
#define MIDI_CHANNEL Manifold::Audio::CHANNEL_TYPE::MIDI 
#endif

#ifndef GROUP_CHANNEL 
#define GROUP_CHANNEL Manifold::Audio::CHANNEL_TYPE::GROUP 
#endif

#ifndef VST_PATH 
#define VST_PATH Manifold::Settings::Pathing::s_vstFolderPath
#endif

#ifndef GET_PARAM_AS_VALUE
    #define GET_PARAM_AS_VALUE(channel, param) channel->getParamAsValue({std::to_string(channel->getId()) + "_" + param})
#endif