#include <immintrin.h>
#include <cstdint>

namespace mylibImageReader
{

void rgbToBgr_AVX2(const uint8_t* src, uint8_t* dst, int width)
{
    int x = 0;
    for (; x + 8 <= width; x += 8)
    {
        __m256i rgb = _mm256_loadu_si256(
            reinterpret_cast<const __m256i*>(src + x * 3)
        );

        const __m256i shuffle = _mm256_setr_epi8(
            2,1,0, 5,4,3, 8,7,6, 11,10,9,
            14,13,12, 17,16,15, 20,19,18, 23,22,21,
            2,1,0, 5,4,3, 8,7,6, 11,10,9,
            14,13,12, 17,16,15, 20,19,18, 23,22,21
        );

        __m256i bgr = _mm256_shuffle_epi8(rgb, shuffle);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(dst + x * 3), bgr);
    }

    for (; x < width; ++x)
    {
        dst[3*x+0] = src[3*x+2];
        dst[3*x+1] = src[3*x+1];
        dst[3*x+2] = src[3*x+0];
    }
}

}
