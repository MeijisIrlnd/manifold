/*
  ==============================================================================

    WindowListener.h
    Created: 27 May 2022 3:08:45am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "../../Macros.h"
namespace Manifold
{
    namespace UI
    {
        class BaseWindow;
        struct WindowListener
        {
            virtual ~WindowListener() {}
            virtual void onWindowClosed(MANIFOLD_UNUSED BaseWindow* w) = 0;
        };
    }
}