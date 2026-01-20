#include <immintrin.h>
#include <cstdint>

namespace mylibImageReader
{

void resizeBilinearRow_AVX2(
    const uint8_t* src0,
    const uint8_t* src1,
    uint8_t* dst,
    int width,
    float wy0,
    float wy1
)
{
    __m256 v0 = _mm256_set1_ps(wy0);
    __m256 v1 = _mm256_set1_ps(wy1);

    for (int x = 0; x + 8 <= width; x += 8)
    {
        __m256 s0 = _mm256_cvtepi32_ps(
            _mm256_cvtepu8_epi32(_mm_loadl_epi64((__m128i*)(src0 + x)))
        );

        __m256 s1 = _mm256_cvtepi32_ps(
            _mm256_cvtepu8_epi32(_mm_loadl_epi64((__m128i*)(src1 + x)))
        );

        __m256 r = _mm256_fmadd_ps(s0, v0, _mm256_mul_ps(s1, v1));
        __m256i ri = _mm256_cvtps_epi32(r);

        for (int i = 0; i < 8; ++i)
            dst[x+i] = (uint8_t)_mm256_extract_epi32(ri, i);
    }
}

}
