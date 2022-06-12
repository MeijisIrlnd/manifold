/*
  ==============================================================================

    ArrangementView.cpp
    Created: 24 Apr 2022 10:21:47pm
    Author:  Syl

  ==============================================================================
*/

#include "ArrangementView.h"

Manifold::UI::ArrangementView::ArrangementView() : 
    m_channelListComponent(),
    m_playlistView(GET_ENGINE()->getPositionTracker()),
    m_horizontalScrollbar(false),
    m_verticalScrollbar(true)
{
    //addAndMakeVisible(&m_channelListComponent);
    addAndMakeVisible(&m_playlistView);
    m_channelListViewport.setScrollBarsShown(false, false, false, false);
    m_channelListViewport.setViewedComponent(&m_channelListComponent);
    m_playlistView.addListener(this);
    m_playlistViewport.setScrollBarsShown(false, false, false, false);
    m_playlistViewport.setViewedComponent(&m_playlistView);
    addAndMakeVisible(&m_channelListViewport);

    addAndMakeVisible(&m_playlistViewport);

    addAndMakeVisible(&m_horizontalScrollbar);
    m_horizontalScrollbar.addListener(this);

    addAndMakeVisible(&m_verticalScrollbar);
    m_verticalScrollbar.addListener(this);
}

Manifold::UI::ArrangementView::~ArrangementView()
{

}

void Manifold::UI::ArrangementView::playlistViewScroll(MANIFOLD_UNUSED double newValue)
{
    //m_zoom = newValue;
    resized();
}

void Manifold::UI::ArrangementView::scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    if (scrollBarThatHasMoved == &m_horizontalScrollbar) {
        m_playlistViewport.setViewPosition(static_cast<int>(newRangeStart), m_playlistViewport.getViewPositionY());
    }
    else if (scrollBarThatHasMoved == &m_verticalScrollbar) {
        m_playlistViewport.setViewPosition(m_playlistViewport.getViewPositionX(), static_cast<int>(newRangeStart));
        m_channelListViewport.setViewPosition(m_channelListViewport.getViewPositionX(), static_cast<int>(newRangeStart));
    }
}

void Manifold::UI::ArrangementView::paint(MANIFOLD_UNUSED juce::Graphics& g)
{
}

void Manifold::UI::ArrangementView::resized()
{

    m_channelListComponent.setBounds(0, 0, getWidth() / 8, getHeight());
    m_playlistView.setBounds(getWidth() / 8, 0, static_cast<int>(getWidth() * m_zoom), getHeight());
    m_horizontalScrollbar.setRangeLimits(m_playlistViewport.getHorizontalScrollBar().getRangeLimit());
    m_channelListViewport.setBounds(0, 0, getWidth() / 8, getHeight() - getHeight() / 64);
    m_verticalScrollbar.setRangeLimits(m_playlistViewport.getVerticalScrollBar().getRangeLimit());
    m_playlistViewport.setBounds(getWidth() / 8, 0, getWidth() - (getWidth() / 8) - (getHeight() / 64), getHeight() - getHeight() / 64);
    m_horizontalScrollbar.setBounds(getWidth() / 8, getHeight() - getHeight() / 64, getWidth() - getWidth() / 8, getHeight() / 64);
    m_verticalScrollbar.setBounds(getWidth() - getHeight() / 64, 0, getWidth() / 64, getHeight() - getHeight() / 64);
}
