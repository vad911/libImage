#pragma once
#include <imageReader/pixelFormat.h>
#include <array>

namespace mylibImageReader
{

class Pixel
{
public:
    explicit Pixel(const PixelFormat& format);

    byte*       data();
    const byte* data() const;

    const PixelFormat& format() const;
    byte bytes() const;

private:
    PixelFormat           m_format;
    std::array<byte, 32>  m_storage{};
};

} // namespace mylibImageReader