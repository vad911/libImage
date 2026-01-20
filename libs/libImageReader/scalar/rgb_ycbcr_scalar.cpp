#include <cstdint>

namespace mylibImageReader
{

void rgbToYCbCr_scalar(const uint8_t* src, uint8_t* dst, int width)
{
    for (int x = 0; x < width; ++x)
    {
        float r = src[3*x+0];
        float g = src[3*x+1];
        float b = src[3*x+2];

        dst[3*x+0] = uint8_t(0.299f*r + 0.587f*g + 0.114f*b);
        dst[3*x+1] = uint8_t(-0.1687f*r - 0.3313f*g + 0.5f*b + 128);
        dst[3*x+2] = uint8_t(0.5f*r - 0.4187f*g - 0.0813f*b + 128);
    }
}

}
