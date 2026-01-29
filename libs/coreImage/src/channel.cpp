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

ChannelView Channel::view() noexcept
{
    return ChannelView(
        m_data.dataPtr(),
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
