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