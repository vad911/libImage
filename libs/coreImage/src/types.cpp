#include <coreImage/types.h>

namespace myCoreImage
{
    std::size_t ChannelElementDesc::bits() const noexcept
    {
        switch (bitDepth)
        {
            case ChannelBitDepth::Bit1:  return 1;
            case ChannelBitDepth::Bit5:  return 5;
            case ChannelBitDepth::Bit8:  return 8;
            case ChannelBitDepth::Bit16: return 16;
            case ChannelBitDepth::Bit32: return 32;
            case ChannelBitDepth::Bit64: return 64;
        }
        return 0;
    }

    std::size_t ChannelElementDesc::bytes() const noexcept
    {
        return (bits() + 7) / 8;
    }

    bool ChannelElementDesc::isFloat() const noexcept
    {
        return dataType == ChannelDataType::Float;
    }

    bool ChannelElementDesc::isInteger() const noexcept
    {
        return dataType == ChannelDataType::UnsignedInt ||
               dataType == ChannelDataType::SignedInt;
    }

    bool ChannelElementDesc::isSigned() const noexcept
    {
        return dataType == ChannelDataType::SignedInt;
    }
}
