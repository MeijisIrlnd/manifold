/*
  ==============================================================================

    ChannelListComponent.h
    Created: 24 Apr 2022 9:00:33pm
    Author:  Syl

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../Audio/ManifoldEngine.h"
#include "Subcomponents/ChannelListItem.h"
using namespace Manifold::UI::Components;
namespace Manifold
{
    namespace UI
    {
        class ChannelListComponent : public juce::Component
        {
        public: 
            ChannelListComponent(Manifold::Audio::ManifoldEngine& engine);
            ~ChannelListComponent() override;
            void mouseUp(const juce::MouseEvent& ev) override;
            void paint(juce::Graphics& g) override;
            void resized() override;
        private: 
            Manifold::Audio::ManifoldEngine& m_engine;
            std::vector<std::unique_ptr<ChannelListItem> > m_channelListItems;
        };
    }
}
