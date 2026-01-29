#pragma once

#include <coreImage/lib_coreImage.h>
#include <coreImage/channel_info.h>
#include <coreImage/channel_data.h>
#include <coreImage/channelView.h>

namespace myCoreImage
{

class COREIMAGE_API Channel
{
public:
    Channel() = default;

    Channel(ChannelInfo info,
            std::size_t width,
            std::size_t height);

    ChannelInfo& info() noexcept { return m_info; }
    const ChannelInfo& info() const noexcept { return m_info; }

    ChannelData& data() noexcept { return m_data; }
    const ChannelData& data() const noexcept { return m_data; }

    ChannelView view() noexcept;
    ChannelView view() const noexcept;

private:
    ChannelInfo m_info;
    ChannelData m_data;
};

} // namespace myCoreImage
