/*
  ==============================================================================

    PlaylistView.cpp
    Created: 23 Apr 2022 4:08:25pm
    Author:  Syl

  ==============================================================================
*/

#include "PlaylistView.h"

namespace Manifold
{
    namespace UI
    {
        PlaylistView::PlaylistView(Manifold::Audio::Core::PositionTracker* positionTracker) : 
            m_playheadPositioner(positionTracker)
        {
            addAndMakeVisible(&m_playheadPositioner);
        }

        PlaylistView::~PlaylistView()
        {
        }

        void PlaylistView::mouseWheelMove(const juce::MouseEvent& ev, const juce::MouseWheelDetails& wheel)
        {
            currentMouseWheel += wheel.deltaY;
            currentMouseWheel = std::clamp(currentMouseWheel, -10.0, 10.0);
            auto mapped = juce::jmap<double>(currentMouseWheel, -10.0, 10.0, 1, 20);
            if (m_listener != nullptr) {
                m_listener->playlistViewScroll(mapped);
            }
            DBG(currentMouseWheel);
        }

        void PlaylistView::paint(juce::Graphics& g)
        {
            g.setColour(juce::Colours::lightblue);
            g.fillAll();
            g.setColour(juce::Colours::black);
            for (auto i = 1; i < 12; i++) {
                g.drawLine(0, (getHeight() / 12) * i, getWidth(), (getHeight() / 12) * i);
            }
        }

        void PlaylistView::resized()
        {
            m_playheadPositioner.setBounds(getLocalBounds());
        }
    }
}