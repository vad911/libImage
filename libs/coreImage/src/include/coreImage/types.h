#pragma once

#include <cstdint>
#include <cstddef>

namespace myCoreImage
{
    using byte = std::uint8_t;

    enum class ChannelDataType : std::uint8_t
    {
        UnsignedInt,
        SignedInt,
        Float
    };

    enum class ChannelBitDepth : std::uint8_t
    {
        Bit1,
        Bit5,
        Bit8,
        Bit16,
        Bit32,
        Bit64
    };

    enum class ChannelSemantic : std::uint8_t
    {
        Undefined,

        Red,
        Green,
        Blue,
        Alpha,

        Gray,
        BlackWhite,

        Cyan,
        Magenta,
        Yellow,
        Key
    };

    struct ChannelElementDesc
    {
        ChannelBitDepth bitDepth{};
        ChannelDataType dataType{};

        std::size_t bits()  const noexcept;
        std::size_t bytes() const noexcept;

        bool isFloat()   const noexcept;
        bool isInteger() const noexcept;
        bool isSigned()  const noexcept;
    };

    struct ChannelElementDesc
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
};  // -- end struct ChannelElementDesc
}   // -- end namespace myCoreImage
