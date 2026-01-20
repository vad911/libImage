#pragma once

#include <imageReader/pixelFormat.h>
#include <vector>
#include <cstddef>
#include <stdexcept>

namespace mylibImageReader
{

class ImageCommon
{
public:
    ImageCommon() = default;

    ImageCommon(
        int width,
        int height,
        const PixelFormat& format
    );

    int width() const noexcept { return m_width; }
    int height() const noexcept { return m_height; }

    const PixelFormat& pixelFormat() const noexcept
    {
        return m_format;
    }

    size_t stride() const noexcept
    {
        return m_stride;
    }

    byte* data() noexcept
    {
        return m_data.data();
    }

    const byte* data() const noexcept
    {
        return m_data.data();
    }

    byte* rowPtr(int y) noexcept
    {
        return m_data.data() + static_cast<size_t>(y) * m_stride;
    }

    const byte* rowPtr(int y) const noexcept
    {
        return m_data.data() + static_cast<size_t>(y) * m_stride;
    }

private:
    int         m_width{0};
    int         m_height{0};
    PixelFormat m_format;
    size_t      m_stride{0};
    std::vector<byte> m_data;
};

} // namespace mylibImageReader
