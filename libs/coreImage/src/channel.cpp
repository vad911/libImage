#include <coreImage/channel.h>

namespace myCoreImage
{

Channel::Channel(ChannelInfo info,
                 std::size_t width,
                 std::size_t height)
    : m_info(info)
    , m_data(width, height, info.elementDesc())
{
}

ChannelInfo& Channel::info() noexcept
{
    return m_info;
}

const ChannelInfo& Channel::info() const noexcept
{
    return m_info;
}

ChannelData& Channel::data() noexcept
{
    return m_data;
}

const ChannelData& Channel::data() const noexcept
{
    return m_data;
}

ChannelView Channel::view() noexcept
{
    return ChannelView(
        m_data.data(),
        m_data.width(),
        m_data.height(),
        m_data.strideBytes(),
        m_data.elementDesc()
    );
}

ChannelView Channel::view() const noexcept
{
    return ChannelView(
        const_cast<void*>(m_data.data()),
        m_data.width(),
        m_data.height(),
        m_data.strideBytes(),
        m_data.elementDesc()
    );
}

} // namespace myCoreImage
