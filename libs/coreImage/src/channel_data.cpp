#include <cassert>
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
    assert(elementDesc.isValid());
    assert(elementDesc.bitDepth != ChannelBitDepth::Bit1);

    m_strideBytes = width * elementDesc.bytesPerElement();
    m_buffer.resize(m_strideBytes * height);
}

void* ChannelData::data() noexcept
{
    return m_buffer.data();
}

const void* ChannelData::data() const noexcept
{
    return m_buffer.data();
}

std::size_t ChannelData::width() const noexcept
{
    return m_width;
}

std::size_t ChannelData::height() const noexcept
{
    return m_height;
}

std::size_t ChannelData::strideBytes() const noexcept
{
    return m_strideBytes;
}

ChannelElementDesc ChannelData::elementDesc() const noexcept
{
    return m_elementDesc;
}

} // namespace myCoreImage
