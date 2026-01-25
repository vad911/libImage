#include <cassert>
#include <vector>
#include <cmath>
#include <cstring>

#include <imageReader/imageCommon.h>

using namespace mylibImageReader;

// объявления
void rgbToYCbCr_scalar(const uint8_t*, uint8_t*, int);
void rgbToYCbCr_AVX2(const uint8_t*, uint8_t*, int);

static bool near(uint8_t a, uint8_t b, int eps = 1)
{
    return std::abs(int(a) - int(b)) <= eps;
}

int main()
{
    constexpr int W = 64;
    constexpr int H = 4;

    PixelFormat rgbFmt = PixelFormat::RGB8();

    ImageCommon src(W, H, rgbFmt);
    ImageCommon dstScalar(W, H, rgbFmt);
    ImageCommon dstSIMD(W, H, rgbFmt);

    // заполняем тестовым паттерном
    for (int y = 0; y < H; ++y)
    {
        uint8_t* row = src.rowPtr(y);
        for (int x = 0; x < W; ++x)
        {
            row[3*x+0] = uint8_t((x * 3) & 255);
            row[3*x+1] = uint8_t((y * 40) & 255);
            row[3*x+2] = uint8_t((x + y) & 255);
        }
    }

    for (int y = 0; y < H; ++y)
    {
        rgbToYCbCr_scalar(src.rowPtr(y), dstScalar.rowPtr(y), W);
        rgbToYCbCr_AVX2  (src.rowPtr(y), dstSIMD.rowPtr(y),   W);
    }

    // сравнение
    for (int y = 0; y < H; ++y)
    {
        const uint8_t* a = dstScalar.rowPtr(y);
        const uint8_t* b = dstSIMD.rowPtr(y);

        for (int i = 0; i < W * 3; ++i)
        {
            assert(near(a[i], b[i]));
        }
    }

    return 0;
}
