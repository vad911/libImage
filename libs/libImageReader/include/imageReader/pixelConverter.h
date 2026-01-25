#pragma once

#include <imageReader/types.h>
#include <imageReader/imageCommon.h>

namespace mylibImageReader
{



class ImageCommon;

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
