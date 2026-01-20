#include <immintrin.h>
#include <cstdint>

namespace mylibImageReader
{

void rgbToYCbCr_AVX2(const uint8_t* src, uint8_t* dst, int width)
{
    const __m256 cYR = _mm256_set1_ps(0.299f);
    const __m256 cYG = _mm256_set1_ps(0.587f);
    const __m256 cYB = _mm256_set1_ps(0.114f);

    const __m256 offset = _mm256_set1_ps(128.f);

    int x = 0;
    for (; x + 8 <= width; x += 8)
    {
        __m256 r = _mm256_cvtepi32_ps(
            _mm256_cvtepu8_epi32(_mm_loadl_epi64((__m128i*)(src + 3*x)))
        );

        __m256 g = _mm256_cvtepi32_ps(
            _mm256_cvtepu8_epi32(_mm_loadl_epi64((__m128i*)(src + 3*x + 1)))
        );

        __m256 b = _mm256_cvtepi32_ps(
            _mm256_cvtepu8_epi32(_mm_loadl_epi64((__m128i*)(src + 3*x + 2)))
        );

        __m256 y = _mm256_fmadd_ps(r, cYR,
                     _mm256_fmadd_ps(g, cYG,
                         _mm256_mul_ps(b, cYB)));

        __m256i yi = _mm256_cvtps_epi32(y);

        for (int i = 0; i < 8; ++i)
            dst[3*(x+i)] = (uint8_t)_mm256_extract_epi32(yi, i);
    }
}

}
