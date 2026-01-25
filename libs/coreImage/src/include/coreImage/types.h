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
}
