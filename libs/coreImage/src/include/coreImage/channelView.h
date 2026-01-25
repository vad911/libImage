#pragma once

#include <cstddef>
#include <coreImage/channelElementDesc.h>

namespace myCoreImage
{

class ChannelView
{
public:
    ChannelView() = default;

    ChannelView(void* data,
                std::size_t width,
                std::size_t height,
                std::size_t strideBytes,
                ChannelElementDesc elementDesc);

    void* data() const noexcept;

    std::size_t width() const noexcept;
    std::size_t height() const noexcept;
    std::size_t strideBytes() const noexcept;

    ChannelElementDesc elementDesc() const noexcept;

    std::size_t bytesPerElement() const noexcept;

    ChannelView subView(std::size_t x,
                        std::size_t y,
                        std::size_t w,
                        std::size_t h) const;

private:
    byte*               m_data = nullptr;
    std::size_t         m_width = 0;
    std::size_t         m_height = 0;
    std::size_t         m_strideBytes = 0;
    ChannelElementDesc  m_elementDesc{};
};

} // namespace myCoreImage
