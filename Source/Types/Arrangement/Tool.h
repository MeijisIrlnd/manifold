/*
  ==============================================================================

    Tool.h
    Created: 28 Oct 2022 4:25:46pm
    Author:  letsm

  ==============================================================================
*/

#pragma once
#include <unordered_map>
#include <utility>
#include <JuceHeader.h>
#include <Types/Tools.h>

namespace Manifold
{
    class Tool
    {
    public: 
        TOOL tool;
        // Tool name, some other shit probably I don't fuckin know..
        std::pair<const void*, int> imageData;
        
    private:

    };

    static std::unordered_map<TOOL, Tool> s_toolLookup = {
        std::make_pair(TOOL::CURSOR, Tool{TOOL::CURSOR, std::make_pair(BinaryData::TLCursor_png, BinaryData::TLCursor_pngSize)}),
        std::make_pair(TOOL::PENCIL, Tool{TOOL::PENCIL, std::make_pair(BinaryData::TLPencil_png, BinaryData::TLPencil_pngSize)}),
        std::make_pair(TOOL::ERASER, Tool{TOOL::ERASER, std::make_pair(BinaryData::TLEraser_png, BinaryData::TLEraser_pngSize)}),
        std::make_pair(TOOL::SCISSOR, Tool{TOOL::SCISSOR, std::make_pair(BinaryData::TLScissor_png, BinaryData::TLScissor_pngSize)}),
        std::make_pair(TOOL::MARQUEE, Tool{TOOL::MARQUEE, std::make_pair(BinaryData::TLMarquee_png, BinaryData::TLMarquee_pngSize)}),
        std::make_pair(TOOL::MUTE, Tool{TOOL::MUTE, std::make_pair(BinaryData::TLMute_png, BinaryData::TLMute_pngSize)})
    };
}