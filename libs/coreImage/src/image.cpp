#include <coreImage/image.h>
#include <coreImage/coreImage.h>
#include <stdexcept>

namespace myCoreImage
{

// ---------------------------
// Конструктор
// ---------------------------
Image::Image(std::size_t width, std::size_t height, const std::vector<ChannelInfo>& channelInfos)
    : m_width(width), m_height(height)
{
    m_channels.reserve(channelInfos.size());
    for (const auto& info : channelInfos)
    {
        m_channels.emplace_back(info, width, height);
    }
}

// ---------------------------
// Доступ к каналам
// ---------------------------
Channel& Image::channel(std::size_t index)
{
    if (index >= m_channels.size())
        throw std::out_of_range("Channel index out of range");
    return m_channels[index];
}

const Channel& Image::channel(std::size_t index) const
{
    if (index >= m_channels.size())
        throw std::out_of_range("Channel index out of range");
    return m_channels[index];
}

// ---------------------------
// Создание из interleaved
// ---------------------------
Image Image::fromInterleaved(
    const std::vector<byte>& imageData,
    std::size_t width,
    std::size_t height,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
)
{
    ChannelArray channels = myCoreImage::fromInterleaved(imageData, width, height, elementDescs.size(), elementDescs, semantics);

    Image img;
    img.m_width = width;
    img.m_height = height;
    img.m_channels = std::move(channels);
    return img;
}

// ---------------------------
// В interleaved
// ---------------------------
std::vector<byte> Image::toInterleaved() const
{
    return myCoreImage::toInterleaved(m_channels);
}

// ============================
// ImageView
// ============================
ImageView::ImageView(Image& image)
    : m_image(image)
{}

ChannelView ImageView::channelView(std::size_t index)
{
    return m_image.channel(index).view();
}

} // namespace myCoreImage
