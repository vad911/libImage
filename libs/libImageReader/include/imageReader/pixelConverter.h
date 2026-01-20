#pragma once

#include <imageReader/imageCommon.h>

namespace mylibImageReader
{

enum class ColorSpace
{
    RGB,
    RGBA,
    Gray,
    YCbCr,
    XYZ,
    Lab,
    LCh
};

class PixelConverter
{
public:
    static void convert(
        const ImageCommon& src,
        ImageCommon& dst,
        ColorSpace dstSpace
    );

private:
    static void convertThreaded(
        const ImageCommon& src,
        ImageCommon& dst,
        ColorSpace dstSpace
    );

    static void convertSingleThread(
        const ImageCommon& src,
        ImageCommon& dst,
        ColorSpace dstSpace
    );
};

} // namespace mylibImageReader
