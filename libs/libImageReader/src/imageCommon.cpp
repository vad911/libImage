#include <imageReader/imageCommon.h>

namespace mylibImageReader
{

ImageCommon::ImageCommon(
    int width,
    int height,
    const PixelFormat& format
)
    : m_width(width)
    , m_height(height)
    , m_format(format)
{
    if (width <= 0 || height <= 0)
        throw std::runtime_error("ImageCommon: invalid image size");

    m_stride = static_cast<size_t>(width) * format.pixelSizeBytes();

    m_data.resize(m_stride * static_cast<size_t>(height));
}

} // namespace mylibImageReader
