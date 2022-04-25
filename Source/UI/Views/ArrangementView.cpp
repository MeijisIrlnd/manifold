/*
  ==============================================================================

    ArrangementView.cpp
    Created: 24 Apr 2022 10:21:47pm
    Author:  Syl

  ==============================================================================
*/

#include "ArrangementView.h"

Manifold::UI::ArrangementView::ArrangementView(Manifold::Audio::ManifoldEngine& engine) : 
    m_engine(engine),
    m_channelListComponent(engine),
    m_playlistView(engine.getPositionTracker()),
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

void Manifold::UI::ArrangementView::playlistViewScroll(double newValue)
{
    //m_zoom = newValue;
    resized();
}

void Manifold::UI::ArrangementView::scrollBarMoved(juce::ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    if (scrollBarThatHasMoved == &m_horizontalScrollbar) {
        m_playlistViewport.setViewPosition(newRangeStart, m_playlistViewport.getViewPositionY());
    }
    else if (scrollBarThatHasMoved == &m_verticalScrollbar) {
        m_playlistViewport.setViewPosition(m_playlistViewport.getViewPositionX(), newRangeStart);
        m_channelListViewport.setViewPosition(m_channelListViewport.getViewPositionX(), newRangeStart);
    }
}

void Manifold::UI::ArrangementView::paint(juce::Graphics& g)
{
}

void Manifold::UI::ArrangementView::resized()
{

    m_channelListComponent.setBounds(0, 0, getWidth() / 8, getHeight());
    m_playlistView.setBounds(getWidth() / 8, 0, getWidth() * m_zoom, getHeight());
    m_horizontalScrollbar.setRangeLimits(m_playlistViewport.getHorizontalScrollBar().getRangeLimit());
    m_channelListViewport.setBounds(0, 0, getWidth() / 8, getHeight() - getHeight() / 64);
    m_verticalScrollbar.setRangeLimits(m_playlistViewport.getVerticalScrollBar().getRangeLimit());
    m_playlistViewport.setBounds(getWidth() / 8, 0, getWidth() - (getWidth() / 8) - (getHeight() / 64), getHeight() - getHeight() / 64);
    m_horizontalScrollbar.setBounds(getWidth() / 8, getHeight() - getHeight() / 64, getWidth() - getWidth() / 8, getHeight() / 64);
    m_verticalScrollbar.setBounds(getWidth() - getHeight() / 64, 0, getWidth() / 64, getHeight() - getHeight() / 64);
}
