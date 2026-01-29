#include <coreImage/channel_data.h>

namespace myCoreImage
{

ChannelData::ChannelData(std::size_t width,
                         std::size_t height,
                         ChannelElementDesc elementDesc)
    : m_width(width)
    , m_height(height)
    , m_elementDesc(elementDesc)
{
    m_strideBytes = width * elementDesc.bytesPerElement();
    m_buffer.resize(m_strideBytes * height);
}

} // namespace myCoreImage
