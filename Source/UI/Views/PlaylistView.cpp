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
        PlaylistView::PlaylistView()
        {
            addAndMakeVisible(&m_playheadPositioner);
            GET_ENGINE()->addListener(this);
        }

        PlaylistView::~PlaylistView()
        {
        }

        void PlaylistView::zoomChanged(const std::pair<double, double>& shownTimeRange)
        {
            for (auto& l : m_channelLanes) {
                l->zoomLevelChanged(shownTimeRange);
            }
        }

        void PlaylistView::onChannelCreated(Audio::InternalChannel* newChannel)
        {
            std::unique_ptr<ChannelLane> currentLane(new ChannelLane(newChannel));
            m_channelLanes.push_back(std::move(currentLane));
            addAndMakeVisible(m_channelLanes.back().get());
            repaint();
        }

        void PlaylistView::onChannelDeleted(MANIFOLD_UNUSED Audio::InternalChannel* toDelete)
        {
        }

        void PlaylistView::mouseWheelMove(const juce::MouseEvent&, const juce::MouseWheelDetails& wheel)
        {
            currentMouseWheel += wheel.deltaY;
            currentMouseWheel = std::clamp(currentMouseWheel, -10.0, 10.0);
            auto mapped = juce::jmap<double>(currentMouseWheel, -10.0, 10.0, 1, 20);
            if (m_listener != nullptr) {
                m_listener->playlistViewScroll(mapped);
            }
            DBG(currentMouseWheel);
        }

        void PlaylistView::paint(MANIFOLD_UNUSED juce::Graphics& g)
        {
            //g.setColour(juce::Colour(0xFFF0F0F0));
            //g.fillAll();
            //g.setColour(juce::Colours::black);
            //for (auto i = 1; i < 12; i++) {
            //    g.drawLine(0, (getHeight() / 12.0f) * static_cast<float>(i), static_cast<float>(getWidth()), (getHeight() / 12.0f) * static_cast<float>(i));
            //}
        }

        void PlaylistView::resized()
        {
            //m_playheadPositioner.setBounds(getLocalBounds());
            for (auto i = 0; i < m_channelLanes.size(); i++) {
                m_channelLanes[i]->setBounds(0, (getHeight() / 12) * i, getWidth(), getHeight() / 12);
            }
        }
    }
}