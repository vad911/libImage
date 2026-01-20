#pragma once

#include <cstdint>
#include <string>

namespace mylibImageReader
{

using byte = uint8_t;

/// Тип хранения одного канала
enum class ChannelType : byte
{
    UInt8,
    UInt16,
    UInt32,
    Float32,
    Float64
};

/// Семантика канала (что он означает)
enum class ChannelSemantic : byte
{
    R,
    G,
    B,
    A,

    Y,
    Cb,
    Cr,

    Gray,

    H,
    S,
    V,

    X,
    Y_XYZ,
    Z,

    L,
    a,
    b,

    C,
    h,

    Unknown
};

/// Описание одного канала
struct ChannelDesc
{
    ChannelSemantic semantic{ChannelSemantic::Unknown};
    ChannelType     type{ChannelType::UInt8};
    byte            bits{8};

    constexpr bool operator==(const ChannelDesc& rhs) const noexcept
    {
        return semantic == rhs.semantic &&
               type == rhs.type &&
               bits == rhs.bits;
    }
};

inline std::string toString(ChannelSemantic s)
{
    switch (s)
    {
    case ChannelSemantic::R: return "R";
    case ChannelSemantic::G: return "G";
    case ChannelSemantic::B: return "B";
    case ChannelSemantic::A: return "A";
    case ChannelSemantic::Y: return "Y";
    case ChannelSemantic::Cb: return "Cb";
    case ChannelSemantic::Cr: return "Cr";
    case ChannelSemantic::Gray: return "Gray";
    case ChannelSemantic::H: return "H";
    case ChannelSemantic::S: return "S";
    case ChannelSemantic::V: return "V";
    case ChannelSemantic::X: return "X";
    case ChannelSemantic::Y_XYZ: return "Y_XYZ";
    case ChannelSemantic::Z: return "Z";
    case ChannelSemantic::L: return "L";
    case ChannelSemantic::a: return "a";
    case ChannelSemantic::b: return "b";
    case ChannelSemantic::C: return "C";
    case ChannelSemantic::h: return "h";
    default: return "Unknown";
    }
}

inline size_t channelTypeSize(ChannelType t)
{
    switch (t)
    {
    case ChannelType::UInt8:   return 1;
    case ChannelType::UInt16:  return 2;
    case ChannelType::UInt32:  return 4;
    case ChannelType::Float32:return 4;
    case ChannelType::Float64:return 8;
    default: return 0;
    }
}

} // namespace mylibImageReader
