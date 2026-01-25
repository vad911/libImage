#pragma once

#include <coreImage/channel_info.h>
#include <coreImage/channel_data.h>

namespace myCoreImage
{
    class Channel
    {
    public:
        ChannelInfo info;
        ChannelData data;

        Channel() = default;

        Channel(const ChannelInfo& channelInfo,
                std::size_t elementCount)
            : info(channelInfo)
            , data(channelInfo, elementCount)
        {
        }
    };
}
