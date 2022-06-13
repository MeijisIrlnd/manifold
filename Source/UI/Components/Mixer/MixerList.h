/*
  ==============================================================================

    List.h
    Created: 13 Jun 2022 2:00:47am
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <concepts>
#include <JuceHeader.h>
#include "../../../Macros.h"
#include "ListItem.h"
namespace Manifold::UI
{
    template <typename T>
    concept IsListElement = std::is_base_of<ListItem, T>::value;

    template <IsListElement T>
    class MixerList : public juce::Component
    {
    public: 
        MixerList(const int channelId, const int maxSlots) :
            m_channelId(channelId), m_maxSlots(maxSlots)
        {
            for (auto i = 0; i < m_maxSlots; i++) {
                m_items.emplace_back(std::make_unique<T>(channelId, i));
                addAndMakeVisible(m_items.back().get());
            }
        }
        ~MixerList() override { }
        void paint(MANIFOLD_UNUSED juce::Graphics& g) override { }
        void resized() override {
            auto h = getHeight() / m_maxSlots;
            for (auto i = 0; i < m_maxSlots; i++) {
                m_items[i]->setBounds(0, h * i, getWidth(), h);
            }
        }

    private: 
        std::vector<std::unique_ptr<T>> m_items;
        const int m_channelId;
        const int m_maxSlots;
    };
    

}