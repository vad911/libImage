#pragma once

#include <cstdint>
#include <cstddef>

namespace myCoreImage
{

using byte = std::uint8_t;

enum class ChannelSemantic : std::uint8_t
{
    Red,
    Green,
    Blue,
    Alpha,
    Gray,
    BlackWhite,
    Unknown
};

enum class ChannelDataType : std::uint8_t
{
    UnsignedInt,
    SignedInt,
    Float
};

enum class ChannelBitDepth : std::uint8_t
{
    Bit1  = 1,
    Bit8  = 8,
    Bit16 = 16,
    Bit32 = 32,
    Bit64 = 64
};

} // namespace myCoreImage
