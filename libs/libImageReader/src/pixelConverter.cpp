#include <imageReader/pixelConverter.h>
#include <imageReader/imageContext.h>

// SIMD forward declarations
namespace mylibImageReader
{
    void rgbToYCbCr_AVX2(const uint8_t*, uint8_t*, int);
    void rgbToYCbCr_scalar(const uint8_t*, uint8_t*, int);
}

namespace mylibImageReader
{

void PixelConverter::convert(
    const ImageCommon& src,
    ImageCommon& dst,
    ColorSpace dstSpace
)
{
    const int pixels = src.width() * src.height();

    bool useThreads =
        pixels >= 256 * 256 &&
        ImageContext::instance().threadCount() > 1;

    if (useThreads)
        convertThreaded(src, dst, dstSpace);
    else
        convertSingleThread(src, dst, dstSpace);
}

void PixelConverter::convertThreaded(
    const ImageCommon& src,
    ImageCommon& dst,
    ColorSpace dstSpace
)
{
    auto& pool = ImageContext::instance().threadPool();

    constexpr int grain = 32;

    pool.parallelFor(0, src.height(), grain,
        [&](int y0, int y1)
    {
        for (int y = y0; y < y1; ++y)
        {
            const uint8_t* srcRow = src.rowPtr(y);
            uint8_t* dstRow = dst.rowPtr(y);

#if defined(MYLIB_ENABLE_AVX2)
            rgbToYCbCr_AVX2(srcRow, dstRow, src.width());
#else
            rgbToYCbCr_scalar(srcRow, dstRow, src.width());
#endif
        }
    });
}

void PixelConverter::convertSingleThread(
    const ImageCommon& src,
    ImageCommon& dst,
    ColorSpace dstSpace
)
{
    for (int y = 0; y < src.height(); ++y)
    {
        const uint8_t* srcRow = src.rowPtr(y);
        uint8_t* dstRow = dst.rowPtr(y);

#if defined(MYLIB_ENABLE_AVX2)
        rgbToYCbCr_AVX2(srcRow, dstRow, src.width());
#else
        rgbToYCbCr_scalar(srcRow, dstRow, src.width());
#endif
    }
}

} // namespace mylibImageReader
