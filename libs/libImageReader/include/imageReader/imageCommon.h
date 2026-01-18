#pragma once
#include <vector>
#include <imageReader/pixelFormat.h>

namespace mylibImageReader {

struct ImageCommon
{
    int width = 0;
    int height = 0;
    size_t strideBytes = 0;

    PixelFormat format;
    std::vector<byte> data;

    size_t stride() const;
    size_t sizeBytes() const;

};

}
