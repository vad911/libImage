#pragma once
#include <imageReader/imageCommon.h>

namespace mylibImageReader
{

class PixelView;

class PixelConverter
{
public:
    static bool convertImage(const ImageCommon& src, ImageCommon& dst);
};

}
