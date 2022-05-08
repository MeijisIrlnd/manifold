/*
  ==============================================================================

    BasePluginListComponent.cpp
    Created: 8 May 2022 1:01:21am
    Author:  Syl

  ==============================================================================
*/

#include "BasePluginListComponent.h"

namespace Manifold
{
    namespace UI
    {
        BasePluginListComponent::BasePluginListComponent(const int maxSlots) : 
            m_maxSlots(maxSlots)
        {
            for (auto i = 0; i < maxSlots; i++) {
                std::unique_ptr<PluginListComponentItem> current(new PluginListComponentItem());
                m_items.push_back(std::move(current));
                addAndMakeVisible(m_items.back().get());
            }
        }

        BasePluginListComponent::~BasePluginListComponent()
        {
        }

        void BasePluginListComponent::paint(MANIFOLD_UNUSED juce::Graphics& g)
        {
        }

        void BasePluginListComponent::resized()
        {
            // So we want a spacer of half an item between each item
            // SO 
            // overallH = (maxItems * h) + (maxItems * (h / 2)) 
            //auto h = static_cast<float>(getHeight()) / (1.5f * m_maxSlots);
            //float nextY = 0;
            //for (auto i = 0; i < m_items.size(); i++) {
            //    nextY += h + (h / 2.0f);
            //    m_items[i]->setBounds(0, static_cast<int>(nextY), getWidth(), static_cast<int>(h));
            //}
            auto h = getHeight() / m_maxSlots;
            for (auto i = 0; i < m_maxSlots; i++) {
                m_items[i]->setBounds(0, h * i, getWidth(), h);
            }
        }
    }
}