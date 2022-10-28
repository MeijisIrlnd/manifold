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
            m_cursors.push_back(std::make_pair(BinaryData::TLCursor_png, BinaryData::TLCursor_pngSize));
            m_cursors.push_back(std::make_pair(BinaryData::TLPencil_png, BinaryData::TLPencil_pngSize));
            m_cursors.push_back(std::make_pair(BinaryData::TLEraser_png, BinaryData::TLEraser_pngSize));
            m_cursors.push_back(std::make_pair(BinaryData::TLScissor_png, BinaryData::TLScissor_pngSize));
            m_cursors.push_back(std::make_pair(BinaryData::TLMarquee_png, BinaryData::TLMarquee_pngSize));
            m_cursors.push_back(std::make_pair(BinaryData::TLMute_png, BinaryData::TLMute_pngSize));
            // Wtf? 
            for (auto i = 0; i < m_cursors.size(); i++) {
                std::unique_ptr<ToolMenuItem> current(new ToolMenuItem(m_cursors[i].first, m_cursors[i].second));
                m_popupItemList.push_back(dynamic_cast<juce::PopupMenu::Item*>(current.get()));
                m_toolMenu.addCustomItem(i + 1, std::move(current), nullptr, "blank");
            }

        }

        PlaylistView::~PlaylistView()
        {
        }

        void PlaylistView::shownTimeRangeChanged(const std::pair<double, double>& shownTimeRange)
        {
            for (auto& l : m_channelLanes) {
                l->shownTimeRangeChanged(shownTimeRange);
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
        void PlaylistView::mouseDown(const juce::MouseEvent& ev)
        {
            if (!ev.mods.isRightButtonDown()) return;
            std::function<void(int)> popupCallback = [this](int res) {
                if (res != 0) {
                    auto cursor = m_cursors[res - 1];
                    juce::MouseCursor newCursor(juce::ImageCache::getFromMemory(cursor.first, cursor.second).rescaled(32, 32, juce::Graphics::lowResamplingQuality), 0, 0);
                    for (auto& l : m_channelLanes) {
                        l->setMouseCursor(newCursor);
                    }
                }
            };

            juce::PopupMenu::Options opts;
            m_toolMenu.showMenuAsync(opts.withMinimumNumColumns(7).withMaximumNumColumns(7), popupCallback);
        }

        void PlaylistView::mouseUp(MANIFOLD_UNUSED const juce::MouseEvent& ev)
        {
            // Does tool still switch? 
            // Also fuck this compilation time 
            juce::PopupMenu::MenuItemIterator menuItemIterator(m_toolMenu, false);
            bool toolSet = false;
            while (menuItemIterator.next())
            {
                auto item = menuItemIterator.getItem();
                if (!toolSet) {
                    if (item.customComponent->isItemHighlighted()) {
                        // Okay so this is the tool to use, manually call? 
                        item.customComponent->triggerMenuItem();
                        toolSet = true;
                    }
                }
                menuItemIterator.getItem().customComponent->setHighlighted(false);
            }
            juce::PopupMenu::dismissAllActiveMenus();
            //for (auto& el : m_popupItemList) {
            //    el->customComponent->setHighlighted(false);
            //}
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