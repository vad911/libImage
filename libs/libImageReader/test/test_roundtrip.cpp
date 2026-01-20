#include <cassert>
#include <vector>
#include <cmath>

using namespace mylibImageReader;

// (пока scalar)
void rgbToYCbCr_scalar(const uint8_t*, uint8_t*, int);

int main()
{
    constexpr int W = 128;

    std::vector<uint8_t> rgb(W * 3);
    std::vector<uint8_t> ycbcr(W * 3);

    for (int i = 0; i < W; ++i)
    {
        rgb[3*i+0] = uint8_t(i);
        rgb[3*i+1] = uint8_t(255 - i);
        rgb[3*i+2] = uint8_t((i * 7) & 255);
    }

    rgbToYCbCr_scalar(rgb.data(), ycbcr.data(), W);

    // пока проверяем диапазоны
    for (int i = 0; i < W * 3; ++i)
    {
        assert(ycbcr[i] <= 255);
    }

    return 0;
}
