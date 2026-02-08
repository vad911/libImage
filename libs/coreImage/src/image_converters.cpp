#include <coreImage/image_converters.h>
#include <stdexcept>
#include <cstring>

namespace myCoreImage {
namespace converters {

 ChannelArray fromPackedRGB565(
        const std::vector<byte>& src,
        std::size_t width,
        std::size_t height
);

ChannelArray fromPackedBW1(
        const std::vector<byte>& src,
        std::size_t width,
        std::size_t height
);



ChannelArray fromInterleaved(const std::vector<byte>& imageData,
                             std::size_t width, std::size_t height,
                             std::size_t numChannels,
                             const std::vector<ChannelElementDesc>& elementDescs,
                             const std::vector<ChannelSemantic>& semantics)
{
    if(numChannels != elementDescs.size() || numChannels != semantics.size())
        throw std::runtime_error("Mismatch channel descriptions");

    ChannelArray channels;
    channels.reserve(numChannels);
    for(size_t i=0; i<numChannels; ++i)
        channels.emplace_back(ChannelInfo(semantics[i], elementDescs[i]), width, height);

    size_t pixelSize = 0;
    for(const auto& desc : elementDescs) pixelSize += desc.bytesPerElement();
    if(imageData.size() != width*height*pixelSize)
        throw std::runtime_error("Image data size mismatch");

    for(size_t y=0; y<height; ++y)
        for(size_t x=0; x<width; ++x)
        {
            size_t pixelOffset = (y*width + x) * pixelSize;
            size_t channelOffset = 0;
            for(size_t c=0; c<numChannels; ++c)
            {
                auto& channel = channels[c];
                size_t bpe = channel.data().elementDesc().bytesPerElement();
                std::uint8_t* dest = static_cast<std::uint8_t*>(channel.data().data()) + y*channel.data().strideBytes() + x*bpe;
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

    for(size_t c=0; c<numChannels; ++c)
    {
        bytesPerChannel[c] = channels[c].data().elementDesc().bytesPerElement();
        pixelSize += bytesPerChannel[c];
    }

    std::vector<byte> imageData(width*height*pixelSize);
    for(size_t y=0; y<height; ++y)
        for(size_t x=0; x<width; ++x)
        {
            size_t pixelOffset = (y*width + x)*pixelSize;
            size_t channelOffset = 0;
            for(size_t c=0; c<numChannels; ++c)
            {
                const auto& channel = channels[c];
                const auto* src = static_cast<const byte*>(channel.data().data()) + y*channel.data().strideBytes() + x*bytesPerChannel[c];
                std::memcpy(imageData.data() + pixelOffset + channelOffset, src, bytesPerChannel[c]);
                channelOffset += bytesPerChannel[c];
            }
        }

    return imageData;
}


ChannelArray fromPacked(
    const std::vector<byte>& src,
    std::size_t width,
    std::size_t height,
    PixelFormat format
)
{
    switch (format)
    {
        case PixelFormat::RGB565:
            return fromPackedRGB565(src, width, height);

        case PixelFormat::BW1:
            return fromPackedBW1(src, width, height);

        default:
            throw std::runtime_error("fromPacked: unsupported PixelFormat");
    }
}



ChannelArray fromPackedRGB565(
    const std::vector<byte>& src,
    std::size_t width,
    std::size_t height
)
{
    const std::size_t expectedSize = width * height * 2;
    if (src.size() != expectedSize)
        throw std::runtime_error("RGB565: invalid buffer size");

    ChannelElementDesc u8desc {
        ChannelDataType::UnsignedInt,
        ChannelBitDepth::Bit8
    };

    ChannelArray channels;
    channels.emplace_back(
        ChannelInfo(ChannelSemantic::Red, u8desc),
        width, height
    );
    channels.emplace_back(
        ChannelInfo(ChannelSemantic::Green, u8desc),
        width, height
    );
    channels.emplace_back(
        ChannelInfo(ChannelSemantic::Blue, u8desc),
        width, height
    );

    auto* r = static_cast<byte*>(channels[0].data().data());
    auto* g = static_cast<byte*>(channels[1].data().data());
    auto* b = static_cast<byte*>(channels[2].data().data());

    for (std::size_t i = 0; i < width * height; ++i)
    {
        std::uint16_t p =
            src[2 * i] |
            (static_cast<std::uint16_t>(src[2 * i + 1]) << 8);

        r[i] = static_cast<byte>(((p >> 11) & 0x1F) * 255 / 31);
        g[i] = static_cast<byte>(((p >> 5)  & 0x3F) * 255 / 63);
        b[i] = static_cast<byte>(( p        & 0x1F) * 255 / 31);
    }

    return channels;
} // -- end func fromPackedRGB565



ChannelArray fromPackedBW1(
    const std::vector<byte>& src,
    std::size_t width,
    std::size_t height
)
{
    const std::size_t bits = width * height;
    const std::size_t expectedSize = (bits + 7) / 8;

    if (src.size() != expectedSize)
        throw std::runtime_error("BW1: invalid buffer size");

    ChannelElementDesc u8desc {
        ChannelDataType::UnsignedInt,
        ChannelBitDepth::Bit8
    };

    ChannelArray channels;
    channels.emplace_back(
        ChannelInfo(ChannelSemantic::Luminance, u8desc),
        width, height
    );

    auto* dst = static_cast<byte*>(channels[0].data().data());

    for (std::size_t i = 0; i < bits; ++i)
    {
        const std::size_t byteIdx = i / 8;
        const std::size_t bitIdx  = 7 - (i % 8);

        dst[i] = (src[byteIdx] & (1 << bitIdx)) ? 255 : 0;
    }

    return channels;
}  // -- end func fromPackedBW1



} // namespace converters
} // namespace myCoreImage
