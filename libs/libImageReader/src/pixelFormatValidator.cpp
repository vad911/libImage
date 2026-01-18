#include <imageReader/pixelFormatValidator.h>

namespace mylibImageReader
{

PixelFormatValidationResult PixelFormatValidator::validate(const PixelFormat& f)
{
    PixelFormatValidationResult r;

    if (f.channelSize == ChannelSize::Bit1 &&
        f.packing != PixelPacking::BW1)
    {
        r.valid = false;
        r.error = "Bit1 allowed only with BW1 packing";
        return r;
    }

    if (f.packing == PixelPacking::RGB565)
    {
        if (f.colorSpace != ColorSpace::RGB ||
            f.layout != ChannelLayout::RGB ||
            f.channelType != ChannelType::UInt)
        {
            r.valid = false;
            r.error = "RGB565 requires RGB UInt layout";
            return r;
        }
    }

    if (!f.hasAlpha() && f.alphaMode == AlphaMode::Premultiplied)
    {
        r.valid = false;
        r.error = "Premultiplied alpha without alpha channel";
        return r;
    }

    if ((f.channelType == ChannelType::Float && f.channelSize != ChannelSize::Bit32) ||
        (f.channelType == ChannelType::Double && f.channelSize != ChannelSize::Bit64))
    {
        r.valid = false;
        r.error = "Invalid channel size for float/double";
        return r;
    }

    return r;
}

}
