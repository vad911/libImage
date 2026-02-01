#include <coreImage/image_converters.h>
#include <stdexcept>
#include <cstring>

namespace myCoreImage
{
namespace converters {

ChannelArray fromInterleaved(
    const std::vector<byte>& imageData,
    std::size_t width,
    std::size_t height,
    std::size_t numChannels,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
)
{
    if(numChannels != elementDescs.size() || numChannels != semantics.size())
        throw std::runtime_error("Mismatch channel descriptions");

    ChannelArray channels;
    channels.reserve(numChannels);
    for(size_t i = 0; i < numChannels; ++i)
        channels.emplace_back(ChannelInfo(semantics[i], elementDescs[i]), width, height);

    size_t pixelSize = 0;
    for(const auto& desc : elementDescs)
        pixelSize += desc.bytesPerElement();

    if(imageData.size() != width * height * pixelSize)
        throw std::runtime_error("Image data size mismatch");

    for(size_t y = 0; y < height; ++y)
        for(size_t x = 0; x < width; ++x)
        {
            size_t pixelOffset = (y * width + x) * pixelSize;
            size_t channelOffset = 0;
            for(size_t c = 0; c < numChannels; ++c)
            {
                auto& channel = channels[c];
                size_t bpe = channel.data().elementDesc().bytesPerElement();
                std::uint8_t* dest = static_cast<std::uint8_t*>(channel.data().data()) + y * channel.data().strideBytes() + x * bpe;
                std::memcpy(dest, imageData.data() + pixelOffset + channelOffset, bpe);
                channelOffset += bpe;
            }
        }

    return channels;
}

std::vector<byte> toInterleaved(const ChannelArray& channels)
{
    if(channels.empty()) return {};

    size_t width = channels[0].data().width();
    size_t height = channels[0].data().height();
    size_t numChannels = channels.size();
    std::vector<size_t> bytesPerChannel(numChannels);
    size_t pixelSize = 0;

    for(size_t c = 0; c < numChannels; ++c)
    {
        bytesPerChannel[c] = channels[c].data().elementDesc().bytesPerElement();
        pixelSize += bytesPerChannel[c];
    }

    std::vector<byte> imageData(width * height * pixelSize);

    for(size_t y = 0; y < height; ++y)
        for(size_t x = 0; x < width; ++x)
        {
            size_t pixelOffset = (y * width + x) * pixelSize;
            size_t channelOffset = 0;
            for(size_t c = 0; c < numChannels; ++c)
            {
                const auto& channel = channels[c];
                const auto* src = static_cast<const byte*>(channel.data().data()) + y * channel.data().strideBytes() + x * bytesPerChannel[c];
                std::memcpy(imageData.data() + pixelOffset + channelOffset, src, bytesPerChannel[c]);
                channelOffset += bytesPerChannel[c];
            }
        }

    return imageData;
}

myCoreImage::Image fromPacked(const std::vector<byte>& src, std::size_t width, std::size_t height, PixelFormat format)
{
    return myCoreImage::Image::fromPacked(src, width, height, format);
}

} // namespace converters
} // namespace myCoreImage
