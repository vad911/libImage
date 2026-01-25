#pragma once

#include <vector>
#include <coreImage/types.h>
#include <coreImage/channelElementDesc.h>

namespace myCoreImage
{

class ChannelData
{
public:
    ChannelData() = default;

    ChannelData(std::size_t width,
                std::size_t height,
                ChannelElementDesc elementDesc);

    void* data() noexcept;
    const void* data() const noexcept;

    std::size_t width() const noexcept;
    std::size_t height() const noexcept;
    std::size_t strideBytes() const noexcept;

    ChannelElementDesc elementDesc() const noexcept;

private:
    std::size_t              m_width  = 0;
    std::size_t              m_height = 0;
    std::size_t              m_strideBytes = 0;
    ChannelElementDesc       m_elementDesc{};
    std::vector<byte>        m_buffer;
};

} // namespace myCoreImage
