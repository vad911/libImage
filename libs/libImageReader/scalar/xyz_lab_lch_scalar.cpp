#include <cmath>

namespace mylibImageReader
{

static inline float f_xyz(float t)
{
    return t > 0.008856f ? std::cbrt(t) : (7.787f * t + 16.f / 116.f);
}

void xyzToLab_scalar(const float* X, const float* Y, const float* Z,
                     float* L, float* a, float* b)
{
    float fx = f_xyz(*X);
    float fy = f_xyz(*Y);
    float fz = f_xyz(*Z);

    *L = 116.f * fy - 16.f;
    *a = 500.f * (fx - fy);
    *b = 200.f * (fy - fz);
}

}
