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

ColorSpace PixelFormat::colorSpace() const
{
    const bool hasR = has(ChannelSemantic::R);
    const bool hasG = has(ChannelSemantic::G);
    const bool hasB = has(ChannelSemantic::B);
    const bool hasA = has(ChannelSemantic::A);

    if (hasR && hasG && hasB)
        return hasA ? ColorSpace::RGBA : ColorSpace::RGB;

    if (has(ChannelSemantic::Gray))
        return ColorSpace::Gray;

    if (has(ChannelSemantic::Y) &&
        has(ChannelSemantic::Cb) &&
        has(ChannelSemantic::Cr))
        return ColorSpace::YCbCr;

    if (has(ChannelSemantic::X) &&
        has(ChannelSemantic::Y_XYZ) &&
        has(ChannelSemantic::Z))
        return ColorSpace::XYZ;

    if (has(ChannelSemantic::L) &&
        has(ChannelSemantic::a) &&
        has(ChannelSemantic::b))
        return ColorSpace::Lab;

    if (has(ChannelSemantic::L) &&
        has(ChannelSemantic::C) &&
        has(ChannelSemantic::h))
        return ColorSpace::LCh;

    return ColorSpace::Unknown;
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
