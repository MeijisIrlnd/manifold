/*
  ==============================================================================

    BaseChannelProcessor.cpp
    Created: 8 May 2022 8:38:06pm
    Author:  Syl

  ==============================================================================
*/

#include "BaseChannelProcessor.h"
namespace Manifold
{
    namespace Audio
    {
        namespace Core
        {
            BaseChannelProcessor::BaseChannelProcessor(CHANNEL_TYPE type, InternalChannel* internalChannel) : 
                m_type(type), 
                m_associatedChannel(internalChannel)
            {
                m_inserts.resize(8);
                m_pan = GET_PARAM_AS_VALUE(m_associatedChannel, "pan");
                m_mute = GET_PARAM_AS_VALUE(m_associatedChannel, "mute");
                m_solo = GET_PARAM_AS_VALUE(m_associatedChannel, "solo");
            }

            BaseChannelProcessor::~BaseChannelProcessor()
            {
            }
        }
    }
}

