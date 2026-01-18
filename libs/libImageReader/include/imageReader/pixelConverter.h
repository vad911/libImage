#pragma once
#include <imageReader/imageCommon.h>

namespace mylibImageReader
{

class PixelConverter
{
public:
    static bool convertImage(const ImageCommon& src, ImageCommon& dst);
};

}
