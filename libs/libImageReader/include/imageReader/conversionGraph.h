#pragma once
#include <imageReader/pixelFormat.h>
#include <vector>

namespace mylibImageReader
{

class ConversionGraph
{
public:
    static std::vector<PixelFormat>
    buildPath(const PixelFormat& src,
              const PixelFormat& dst);

private:
    static PixelFormat canonicalRGB();
};

}
