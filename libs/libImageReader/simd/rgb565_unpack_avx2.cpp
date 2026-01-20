#include <immintrin.h>
#include <cstdint>

namespace mylibImageReader
{

void rgb565ToRgb8_AVX2(const uint16_t* src, uint8_t* dst, int width)
{
    int x = 0;
    for (; x + 16 <= width; x += 16)
    {
        __m256i v = _mm256_loadu_si256(
            reinterpret_cast<const __m256i*>(src + x)
        );

        __m256i r = _mm256_and_si256(_mm256_srli_epi16(v, 11), _mm256_set1_epi16(0x1F));
        __m256i g = _mm256_and_si256(_mm256_srli_epi16(v, 5),  _mm256_set1_epi16(0x3F));
        __m256i b = _mm256_and_si256(v, _mm256_set1_epi16(0x1F));

        r = _mm256_slli_epi16(r, 3);
        g = _mm256_slli_epi16(g, 2);
        b = _mm256_slli_epi16(b, 3);

        // scalar store fallback for simplicity
        for (int i = 0; i < 16; ++i)
        {
            dst[3*(x+i)+0] = ((uint8_t*)&r)[2*i];
            dst[3*(x+i)+1] = ((uint8_t*)&g)[2*i];
            dst[3*(x+i)+2] = ((uint8_t*)&b)[2*i];
        }
    }
}
}
