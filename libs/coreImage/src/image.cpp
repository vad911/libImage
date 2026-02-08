#include <coreImage/image.h>
#include <coreImage/image_converters.h>
#include <coreImage/transform.h>
#include <stdexcept>
#include <cstring>

namespace cv = myCoreImage::converters;
namespace tr = myCoreImage::transform;

namespace myCoreImage {

// ----------------
// Image
// ----------------
Image::Image(std::size_t width, std::size_t height, const std::vector<ChannelInfo>& channelInfos)
    : m_width(width), m_height(height)
{
    m_channels.reserve(channelInfos.size());
    for (const auto& info : channelInfos)
        m_channels.emplace_back(info, width, height);
}

Channel& Image::channel(std::size_t index)
{
    if(index >= m_channels.size()) throw std::out_of_range("Channel index out of range");
    return m_channels[index];
}

const Channel& Image::channel(std::size_t index) const
{
    if(index >= m_channels.size()) throw std::out_of_range("Channel index out of range");
    return m_channels[index];
}

Image Image::fromInterleaved(const std::vector<byte>& imageData,
                             std::size_t width, std::size_t height,
                             const std::vector<ChannelElementDesc>& elementDescs,
                             const std::vector<ChannelSemantic>& semantics)
{
    ChannelArray channels = cv::fromInterleaved(imageData, width, height, elementDescs.size(), elementDescs, semantics);
    Image img;
    img.m_width = width;
    img.m_height = height;
    img.m_channels = std::move(channels);
    return img;
}

std::vector<byte> Image::toInterleaved() const
{
    return cv::toInterleaved(m_channels);
}


Image Image::fromPacked(
    const std::vector<byte>& src,
    std::size_t width,
    std::size_t height,
    PixelFormat format
)
{
    ChannelArray channels = converters::fromPacked(src, width, height, format);

    Image img;
    img.m_width = width;
    img.m_height = height;
    img.m_channels = std::move(channels);
    return img;
}


Image Image::resized(std::size_t newWidth, std::size_t newHeight) const
{
    return tr::resize(*this, newWidth, newHeight);
}

Image Image::rotated(double angleDegrees) const
{
    return tr::rotate(*this, angleDegrees);
}

} // namespace myCoreImage
