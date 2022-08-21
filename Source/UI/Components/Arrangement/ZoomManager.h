/*
  ==============================================================================

    ZoomManager.h
    Created: 9 Jul 2022 10:44:51pm
    Author:  letsm

  ==============================================================================
*/

#pragma once
#include <mutex>
#include <JuceHeader.h>
#include "../../../Macros.h"
namespace Manifold
{
    class ZoomManager
    {
    protected: 
        ZoomManager();
    public: 
        struct Listener
        {
            virtual ~Listener() { }
            virtual void onZoomLevelChanged(double newZoomLevel) = 0;
        };

        ~ZoomManager();
        ZoomManager(const ZoomManager& other) = delete;
        ZoomManager(ZoomManager&& other) = delete;
        ZoomManager& operator=(const ZoomManager& other) = delete;
        static ZoomManager* getInstance();
        void addListener(Listener* toAdd);
        void removeListener(Listener* toRemove);
        MANIFOLD_INLINE void setZoomLevel(double zoomLevel) { 
            m_zoomLevel = zoomLevel; 
            for (auto& l : m_zoomListeners) {
                l->onZoomLevelChanged(m_zoomLevel);
            }
        }
        MANIFOLD_INLINE double getZoomLevel() { return m_zoomLevel; }
    private: 
        static std::mutex m_mutex;
        static ZoomManager* m_instance;
        double m_zoomLevel{ 1 };
        std::vector<Listener*> m_zoomListeners;
    };
}