#include <imageReader/imageCommon.h>


size_t ImageCommon::stride() const
{
    return static_cast<size_t>(width) * format.bytesPerPixel();
}

size_t ImageCommon::sizeBytes() const
{
    return stride() * height;
}