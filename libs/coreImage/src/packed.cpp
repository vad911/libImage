#include <coreImage/image.h>
#include <stdexcept>

namespace myCoreImage
{
    Image Image::from_packed(
        const std::vector<byte>& src,
        size_t w,
        size_t h,
        PixelFormat format)
    {
        if (format == PixelFormat::RGB565)
        {
            ChannelElementDesc desc{ ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 };

            Image img(w, h, {
                { ChannelSemantic::Red,   desc },
                { ChannelSemantic::Green, desc },
                { ChannelSemantic::Blue,  desc }
            });

            auto* r = static_cast<byte*>(img.channels()[0].data().data());
            auto* g = static_cast<byte*>(img.channels()[1].data().data());
            auto* b = static_cast<byte*>(img.channels()[2].data().data());

            const std::uint16_t* pixels =
                reinterpret_cast<const std::uint16_t*>(src.data());

            for (size_t i = 0; i < w * h; ++i)
            {
                std::uint16_t p = pixels[i];
                r[i] = ((p >> 11) & 0x1F) * 255 / 31;
                g[i] = ((p >> 5)  & 0x3F) * 255 / 63;
                b[i] = (p & 0x1F) * 255 / 31;
            }
            return img;
        }

        if (format == PixelFormat::BW1)
        {
            ChannelElementDesc desc{ ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 };
            Image img(w, h, { { ChannelSemantic::Gray, desc } });

            auto* gray = static_cast<byte*>(img.channels()[0].data().data());

            for (size_t i = 0; i < w * h; ++i)
            {
                byte bit = (src[i / 8] >> (7 - (i % 8))) & 1;
                gray[i] = bit ? 255 : 0;
            }
            return img;
        }

        throw std::runtime_error("Unsupported PixelFormat");
    }
}
