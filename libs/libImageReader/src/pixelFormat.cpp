#include <imageReader/pixelFormat.h>

namespace mylibImageReader
{

byte PixelFormat::channels() const
{
    switch (layout)
    {
    case ChannelLayout::Y:    return 1;
    case ChannelLayout::YA:   return 2;
    case ChannelLayout::RGB:
    case ChannelLayout::BGR:
    case ChannelLayout::HSV:
    case ChannelLayout::Lab:
    case ChannelLayout::LCh:  return 3;
    case ChannelLayout::RGBA:
    case ChannelLayout::BGRA:
    case ChannelLayout::HSVA: return 4;
    }
    return 0;
}

byte PixelFormat::bytesPerPixel() const
{
    if (packing == PixelPacking::RGB565) return 2;
    if (channelSize == ChannelSize::Bit1) return 1;
    return channels() * (static_cast<byte>(channelSize) / 8);
}

bool PixelFormat::hasAlpha() const
{
    return layout == ChannelLayout::YA ||
           layout == ChannelLayout::RGBA ||
           layout == ChannelLayout::BGRA ||
           layout == ChannelLayout::HSVA;
}

}
