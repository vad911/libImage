#include <coreImage/image.h>
#include <coreImage/image_converters.h>
#include <stdexcept>
#include <cstring>

namespace myCoreImage
{

Image::Image(std::size_t width, std::size_t height, const std::vector<ChannelInfo>& channelInfos)
    : m_width(width), m_height(height)
{
    m_channels.reserve(channelInfos.size());
    for (const auto& info : channelInfos)
    {
        m_channels.emplace_back(info, width, height);
    }
}

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

Image Image::fromInterleaved(
    const std::vector<byte>& imageData,
    std::size_t width,
    std::size_t height,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
)
{
    ChannelArray channels = myCoreImage::fromInterleaved(
        imageData, width, height, elementDescs.size(), elementDescs, semantics);

    Image img;
    img.m_width = width;
    img.m_height = height;
    img.m_channels = std::move(channels);
    return img;
}

std::vector<byte> Image::toInterleaved() const
{
    return myCoreImage::toInterleaved(m_channels);
}

Image Image::fromPacked(const std::vector<byte>& src, std::size_t w, std::size_t h, PixelFormat format)
{
    if (format == PixelFormat::RGB565)
    {
        ChannelElementDesc desc{ ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 };

        Image img(w, h, {
            { ChannelSemantic::Red,   desc },
            { ChannelSemantic::Green, desc },
            { ChannelSemantic::Blue,  desc }
        });

        // используем non-const dataPtr()
        byte* r = img.channels()[0].data().dataPtr();
        byte* g = img.channels()[1].data().dataPtr();
        byte* b = img.channels()[2].data().dataPtr();

        const std::uint16_t* pixels = reinterpret_cast<const std::uint16_t*>(src.data());

        for (size_t i = 0; i < w * h; ++i)
        {
            std::uint16_t p = pixels[i];
            r[i] = ((p >> 11) & 0x1F) * 255 / 31;
            g[i] = ((p >> 5) & 0x3F) * 255 / 63;
            b[i] = (p & 0x1F) * 255 / 31;
        }
        return img;
    }

    if (format == PixelFormat::BW1)
    {
        ChannelElementDesc desc{ ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 };
        Image img(w, h, { { ChannelSemantic::Gray, desc } });

        byte* gray = img.channels()[0].data().dataPtr();

        for (size_t i = 0; i < w * h; ++i)
        {
            byte bit = (src[i / 8] >> (7 - (i % 8))) & 1;
            gray[i] = bit ? 255 : 0;
        }
        return img;
    }

    throw std::runtime_error("Unsupported PixelFormat");
}

} // namespace myCoreImage
