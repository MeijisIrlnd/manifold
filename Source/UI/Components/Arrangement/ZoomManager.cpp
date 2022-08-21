/*
  ==============================================================================

    ZoomManager.cpp
    Created: 9 Jul 2022 10:44:52pm
    Author:  letsm

  ==============================================================================
*/

#include "ZoomManager.h"
namespace Manifold
{
    std::mutex ZoomManager::m_mutex;
    ZoomManager* ZoomManager::m_instance{ nullptr };

    ZoomManager::ZoomManager()
    {

    }

    ZoomManager::~ZoomManager()
    {
        delete m_instance;
        m_instance = nullptr;
    }

    ZoomManager* ZoomManager::getInstance()
    {
        std::scoped_lock<std::mutex> sl(m_mutex);
        if(m_instance == nullptr) { 
            m_instance = new ZoomManager();
        }
        return m_instance;
    }

    void ZoomManager::addListener(Listener* toAdd)
    {
        m_zoomListeners.push_back(toAdd);
    }

    void ZoomManager::removeListener(Listener* toRemove)
    {
        auto it = std::find(m_zoomListeners.begin(), m_zoomListeners.end(), toRemove);
        if (it != m_zoomListeners.end()) {
            m_zoomListeners.erase(it);
        }
    }
}