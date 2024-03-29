/*
  ==============================================================================

    PositionTracker.cpp
    Created: 23 Apr 2022 2:53:50am
    Author:  Syl

  ==============================================================================
*/

#include "PositionTracker.h"
#include <Types/Channel/AudioLaneData.h>
namespace Manifold::Audio::Core
{
    std::mutex PositionTracker::m_mutex;
    PositionTracker* PositionTracker::m_instance{ nullptr };

    PositionTracker* PositionTracker::getInstance()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        if (m_instance == nullptr) {
            m_instance = new PositionTracker();
        }
        return m_instance;
    }

    void PositionTracker::shutdown()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        delete m_instance;
        m_instance = nullptr;
    }

    PositionTracker::~PositionTracker()
    {

    }

}
