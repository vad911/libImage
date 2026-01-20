#include <cassert>
#include <cmath>

using namespace mylibImageReader;

// объявления
void xyzToLab_scalar(const float*, const float*, const float*, float*, float*, float*);
void xyzToLab_AVX2(const float*, const float*, const float*, float*, float*, float*);

static bool near(float a, float b, float eps = 1e-3f)
{
    return std::fabs(a - b) < eps;
}

int main()
{
    alignas(32) float X[8] = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f };
    alignas(32) float Y[8] = { 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f };
    alignas(32) float Z[8] = { 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f };

    float Ls[8], as[8], bs[8];
    float Lv[8], av[8], bv[8];

    for (int i = 0; i < 8; ++i)
    {
        xyzToLab_scalar(&X[i], &Y[i], &Z[i], &Ls[i], &as[i], &bs[i]);
    }

    xyzToLab_AVX2(X, Y, Z, Lv, av, bv);

    for (int i = 0; i < 8; ++i)
    {
        assert(near(Ls[i], Lv[i]));
        assert(near(as[i], av[i]));
        assert(near(bs[i], bv[i]));
    }

    return 0;
}
