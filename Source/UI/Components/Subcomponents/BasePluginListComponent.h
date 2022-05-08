/*
  ==============================================================================

    BasePluginListComponent.h
    Created: 8 May 2022 1:01:21am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include "../../../Macros.h"
#include "PluginListComponentItem.h"
namespace Manifold
{
    namespace UI
    {
        class BasePluginListComponent : public juce::Component
        {
        public: 
            BasePluginListComponent(const int maxSlots);
            virtual ~BasePluginListComponent() override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        protected: 
            std::vector<std::unique_ptr<PluginListComponentItem> > m_items;
            const int m_maxSlots;
        };
    }
}