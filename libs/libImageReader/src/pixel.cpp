#include <imageReader/pixel.h>

namespace mylibImageReader
{

Pixel::Pixel(const PixelFormat& format)
    : m_format(format)
{
}

byte* Pixel::data()
{
    return m_storage.data();
}

const byte* Pixel::data() const
{
    return m_storage.data();
}

const PixelFormat& Pixel::format() const
{
    return m_format;
}

byte Pixel::bytes() const
{
    return m_format.bytesPerPixel();
}

} // namespace mylibImageReader