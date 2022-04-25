/*
  ==============================================================================

    ViewListener.h
    Created: 23 Apr 2022 5:46:35pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
namespace Manifold
{
    namespace UI
    {
        struct ViewListener
        {
            virtual ~ViewListener() { }
            virtual void playlistViewScroll(double newVal) = 0;
        };
    }
}