/*
  ==============================================================================

    Channel.h
    Created: 24 Apr 2022 9:25:47pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Macros.h"
namespace Manifold
{
    namespace Audio
    {
        class InternalChannel
        {
        public: 
            InternalChannel(int internalId, std::string name);
            InternalChannel(const InternalChannel& other);
            void rename(const std::string& newName);
            MANIFOLD_INLINE const std::string& getName() const { return m_name; }
        private: 
            std::string m_name;
            const int m_internalId;
        };
    }
}