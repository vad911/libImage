#pragma once

#include <coreImage/channel_info.h>
#include <coreImage/channel_data.h>
#include <coreImage/channelView.h>

namespace myCoreImage
{

class Channel
{
public:
    Channel() = default;

    Channel(ChannelInfo info,
            std::size_t width,
            std::size_t height);

    ChannelInfo& info() noexcept;
    const ChannelInfo& info() const noexcept;

    ChannelData& data() noexcept;
    const ChannelData& data() const noexcept;

    ChannelView view() noexcept;
    ChannelView view() const noexcept;

private:
    ChannelInfo m_info;
    ChannelData m_data;
};

} // namespace myCoreImage
