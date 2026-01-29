#pragma once

#include <vector>
#include <coreImage/lib_coreImage.h>
#include <coreImage/types.h>
#include <coreImage/channelElementDesc.h>

namespace myCoreImage
{

class COREIMAGE_API ChannelData
{
public:
    ChannelData() = default;

    ChannelData(std::size_t width,
                std::size_t height,
                ChannelElementDesc elementDesc);

    void* data() noexcept { return m_buffer.data(); }
    const void* data() const noexcept { return m_buffer.data(); }

    byte* dataPtr() noexcept { return m_buffer.data(); }
    // const byte* dataPtr() const noexcept { return m_buffer.data(); }

    std::size_t width() const noexcept { return m_width; }
    std::size_t height() const noexcept { return m_height; }
    std::size_t strideBytes() const noexcept { return m_strideBytes; }

    ChannelElementDesc elementDesc() const noexcept { return m_elementDesc; }

private:
    std::size_t        m_width  = 0;
    std::size_t        m_height = 0;
    std::size_t        m_strideBytes = 0;
    ChannelElementDesc m_elementDesc{};
    std::vector<byte>  m_buffer;
};

} // namespace myCoreImage
