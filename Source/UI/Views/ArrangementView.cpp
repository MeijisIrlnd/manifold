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

    addAndMakeVisible(&m_timelineComponent);
}

Manifold::UI::ArrangementView::~ArrangementView()
{

}

void Manifold::UI::ArrangementView::mouseWheelMove(MANIFOLD_UNUSED const juce::MouseEvent& ev, const juce::MouseWheelDetails& wheel)
{
    auto delta = wheel.deltaY;
    DBG(delta);
    m_timelineComponent.setTimeAmtToShow(std::max(m_timelineComponent.getTimeAmtToShow() + delta, 0.25));
    m_playlistView.zoomChanged(m_timelineComponent.getTimeRangeToShow());
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
    auto yStart = getHeight() / 24;
    m_channelListComponent.setBounds(0, yStart, getWidth() / 8, getHeight() - yStart);
    //m_playlistView.setBounds(getWidth() / 8, yStart, static_cast<int>(getWidth() * m_zoom), getHeight() - yStart);
    m_playlistView.setBounds(getWidth() / 8, yStart, getWidth() - getWidth() / 8 - getWidth() / 64, getHeight() - yStart);
    m_horizontalScrollbar.setRangeLimits(m_playlistViewport.getHorizontalScrollBar().getRangeLimit());
    m_channelListViewport.setBounds(0, yStart, getWidth() / 8, getHeight() - getHeight() / 64 - yStart);
    m_verticalScrollbar.setRangeLimits(m_playlistViewport.getVerticalScrollBar().getRangeLimit());
    m_playlistViewport.setBounds(getWidth() / 8, yStart, getWidth() - (getWidth() / 8) - (getHeight() / 64), getHeight() - getHeight() / 64 - yStart);
    m_horizontalScrollbar.setBounds(getWidth() / 8, getHeight() - getHeight() / 64, getWidth() - getWidth() / 8, getHeight() / 64);
    m_verticalScrollbar.setBounds(getWidth() - getHeight() / 64, yStart, getWidth() / 64, getHeight() - getHeight() / 64 - yStart);
    auto localBounds = getLocalBounds();
    m_timelineComponent.setBounds(m_playlistViewport.getX(), 0, getWidth() - m_playlistViewport.getX(), getHeight());
}
