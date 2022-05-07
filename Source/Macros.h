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

#ifndef GET_ENGINE
#define GET_ENGINE Manifold::Audio::ManifoldEngine::getInstance()
#endif