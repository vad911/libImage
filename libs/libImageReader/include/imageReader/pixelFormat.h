#pragma once
#include <imageReader/types.h>


// namespace mli = mylibImageReader

namespace mylibImageReader
{

enum class ColorSpace : byte
{
    Gray,
    RGB,
    HSV,
    Lab,
    LCh
};

enum class ChannelLayout : byte
{
    Y,
    YA,
    RGB,
    BGR,
    RGBA,
    BGRA,
    HSV,
    HSVA,
    Lab,
    LCh
};

enum class ChannelType : byte
{
    UInt,
    Float,
    Double
};

enum class ChannelSize : byte
{
    Bit1  = 1,
    Bit8  = 8,
    Bit16 = 16,
    Bit32 = 32,
    Bit64 = 64
};

enum class PixelPacking : byte
{
    None,
    BW1,
    RGB565
};

enum class AlphaMode : byte
{
    Straight,
    Premultiplied
};

struct PixelFormat
{
    ColorSpace    colorSpace;
    ChannelLayout layout;
    ChannelType   channelType;
    ChannelSize   channelSize;
    PixelPacking  packing;
    AlphaMode     alphaMode = AlphaMode::Straight;

    byte channels() const;
    byte bytesPerPixel() const;
    bool hasAlpha() const;
};

}
