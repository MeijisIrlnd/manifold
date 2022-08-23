/*
  ==============================================================================

    ReferenceCountedObject.h
    Created: 22 Aug 2022 2:24:47am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <algorithm>
namespace Manifold
{
    template<typename T>
    struct ReferenceCountedObject
    {
        T data;
        int numReferences{ 0 };
        ReferenceCountedObject<T>(T&& object) : data(object)
        {
           
        }

        void operator++() {
            ++numReferences;
        }

        void operator--() {
            numReferences = std::max(0, --numReferences);
        }
    };
}