#pragma once

#include <coreImage/lib_coreImage.h>
#include <coreImage/types.h>

namespace myCoreImage
{

struct COREIMAGE_API ChannelElementDesc
{
    ChannelDataType dataType{};
    ChannelBitDepth bitDepth{};

    constexpr bool isValid() const noexcept
    {
        if (dataType == ChannelDataType::Float)
        {
            return bitDepth == ChannelBitDepth::Bit16 ||
                   bitDepth == ChannelBitDepth::Bit32 ||
                   bitDepth == ChannelBitDepth::Bit64;
        }

        if (dataType == ChannelDataType::UnsignedInt)
        {
            return bitDepth == ChannelBitDepth::Bit1 ||
                   bitDepth == ChannelBitDepth::Bit8 ||
                   bitDepth == ChannelBitDepth::Bit16 ||
                   bitDepth == ChannelBitDepth::Bit32 ||
                   bitDepth == ChannelBitDepth::Bit64;
        }

        if (dataType == ChannelDataType::SignedInt)
        {
            return bitDepth == ChannelBitDepth::Bit8 ||
                   bitDepth == ChannelBitDepth::Bit16 ||
                   bitDepth == ChannelBitDepth::Bit32 ||
                   bitDepth == ChannelBitDepth::Bit64;
        }

        return false;
    }

    constexpr std::size_t bytesPerElement() const noexcept
    {
        return static_cast<std::size_t>(bitDepth) / 8;
    }
};

} // namespace myCoreImage
