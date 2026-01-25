#include <coreImage/coreImage.h>
#include <stdexcept>

namespace myCoreImage
{

ChannelArray fromInterleaved(
    const std::vector<byte>& imageData,
    std::size_t width,
    std::size_t height,
    std::size_t numChannels,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
)
{
    if (numChannels != elementDescs.size() || numChannels != semantics.size())
        throw std::runtime_error("Mismatch in channel descriptions");

    // Создаём каналы
    ChannelArray channels;
    channels.reserve(numChannels);
    for (std::size_t i = 0; i < numChannels; ++i)
    {
        ChannelInfo info(semantics[i], elementDescs[i]);
        channels.emplace_back(info, width, height);
    }

    std::size_t pixelSize = 0;
    for (const auto& desc : elementDescs)
        pixelSize += desc.bytesPerElement();

    if (imageData.size() != width * height * pixelSize)
        throw std::runtime_error("Image data size does not match width*height*pixelSize");

    // Распаковываем interleaved -> planar
    for (std::size_t y = 0; y < height; ++y)
    {
        for (std::size_t x = 0; x < width; ++x)
        {
            std::size_t pixelOffset = (y * width + x) * pixelSize;
            std::size_t channelOffset = 0;

            for (std::size_t c = 0; c < numChannels; ++c)
            {
                auto& channel = channels[c];
                auto bytesPerElement = channel.data().elementDesc().bytesPerElement();
                std::uint8_t* dest = static_cast<std::uint8_t*>(channel.data().data()) + y*channel.data().strideBytes() + x*bytesPerElement;

                // копируем байты для одного элемента
                for (std::size_t b = 0; b < bytesPerElement; ++b)
                {
                    dest[b] = imageData[pixelOffset + channelOffset + b];
                }

                channelOffset += bytesPerElement;
            }
        }
    }

    return channels;
}

std::vector<byte> toInterleaved(const ChannelArray& channels)
{
    if (channels.empty())
        return {};

    std::size_t width = channels[0].data().width();
    std::size_t height = channels[0].data().height();
    std::size_t numChannels = channels.size();

    std::vector<std::size_t> bytesPerChannel(numChannels);
    std::size_t pixelSize = 0;

    for (std::size_t c = 0; c < numChannels; ++c)
    {
        bytesPerChannel[c] = channels[c].data().elementDesc().bytesPerElement();
        pixelSize += bytesPerChannel[c];
    }

    std::vector<byte> imageData(width * height * pixelSize);

    for (std::size_t y = 0; y < height; ++y)
    {
        for (std::size_t x = 0; x < width; ++x)
        {
            std::size_t pixelOffset = (y * width + x) * pixelSize;
            std::size_t channelOffset = 0;

            for (std::size_t c = 0; c < numChannels; ++c)
            {
                const auto& channel = channels[c];
                const auto* src = static_cast<const byte*>(channel.data().data()) + y*channel.data().strideBytes() + x*bytesPerChannel[c];
                for (std::size_t b = 0; b < bytesPerChannel[c]; ++b)
                {
                    imageData[pixelOffset + channelOffset + b] = src[b];
                }
                channelOffset += bytesPerChannel[c];
            }
        }
    }

    return imageData;
}

} // namespace myCoreImage
