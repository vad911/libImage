#include <immintrin.h>
#include <cmath>

namespace mylibImageReader
{

static inline __m256 f_xyz(__m256 t)
{
    const __m256 eps = _mm256_set1_ps(0.008856f);
    const __m256 k   = _mm256_set1_ps(7.787f);
    const __m256 c   = _mm256_set1_ps(16.0f / 116.0f);

    __m256 mask = _mm256_cmp_ps(t, eps, _CMP_GT_OS);
    __m256 lin  = _mm256_add_ps(_mm256_mul_ps(k, t), c);

    return _mm256_blendv_ps(lin, _mm256_cbrt_ps(t), mask);
}

void xyzToLab_AVX2(const float* X, const float* Y, const float* Z,
                   float* L, float* a, float* b)
{
    __m256 fx = f_xyz(_mm256_loadu_ps(X));
    __m256 fy = f_xyz(_mm256_loadu_ps(Y));
    __m256 fz = f_xyz(_mm256_loadu_ps(Z));

    _mm256_storeu_ps(L, _mm256_fmadd_ps(fy, _mm256_set1_ps(116.f), _mm256_set1_ps(-16.f)));
    _mm256_storeu_ps(a, _mm256_mul_ps(_mm256_sub_ps(fx, fy), _mm256_set1_ps(500.f)));
    _mm256_storeu_ps(b, _mm256_mul_ps(_mm256_sub_ps(fy, fz), _mm256_set1_ps(200.f)));
}

}
