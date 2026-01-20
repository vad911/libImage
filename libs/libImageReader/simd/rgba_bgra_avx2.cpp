#include <immintrin.h>
#include <cstdint>

namespace mylibImageReader
{

void rgbaToBgra_AVX2(const uint8_t* src, uint8_t* dst, int width)
{
    const __m256i shuffle = _mm256_setr_epi8(
        2,1,0,3, 6,5,4,7, 10,9,8,11, 14,13,12,15,
        18,17,16,19, 22,21,20,23, 26,25,24,27, 30,29,28,31
    );

    int x = 0;
    for (; x + 8 <= width; x += 8)
    {
        __m256i v = _mm256_loadu_si256(
            reinterpret_cast<const __m256i*>(src + x * 4)
        );

        __m256i r = _mm256_shuffle_epi8(v, shuffle);
        _mm256_storeu_si256(
            reinterpret_cast<__m256i*>(dst + x * 4), r
        );
    }

    for (; x < width; ++x)
    {
        dst[4*x+0] = src[4*x+2];
        dst[4*x+1] = src[4*x+1];
        dst[4*x+2] = src[4*x+0];
        dst[4*x+3] = src[4*x+3];
    }
}

}
