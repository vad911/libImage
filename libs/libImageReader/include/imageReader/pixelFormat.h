#pragma once

#include <imageReader/channel.h>
#include <vector>
#include <stdexcept>

namespace mylibImageReader
{

class PixelFormat
{
public:
    PixelFormat() = default;

    explicit PixelFormat(std::vector<ChannelDesc> channels)
        : m_channels(std::move(channels))
    {
        validate();
    }

    const std::vector<ChannelDesc>& channels() const noexcept
    {
        return m_channels;
    }

    size_t channelCount() const noexcept
    {
        return m_channels.size();
    }

    size_t pixelSizeBytes() const noexcept
    {
        size_t size = 0;
        for (const auto& c : m_channels)
            size += channelTypeSize(c.type);
        return size;
    }

    bool hasAlpha() const noexcept
    {
        for (const auto& c : m_channels)
            if (c.semantic == ChannelSemantic::A)
                return true;
        return false;
    }

    bool operator==(const PixelFormat& rhs) const noexcept
    {
        return m_channels == rhs.m_channels;
    }

    static PixelFormat RGB8()
    {
        return PixelFormat({
            {ChannelSemantic::R, ChannelType::UInt8, 8},
            {ChannelSemantic::G, ChannelType::UInt8, 8},
            {ChannelSemantic::B, ChannelType::UInt8, 8}
        });
    }

    static PixelFormat RGBA8()
    {
        return PixelFormat({
            {ChannelSemantic::R, ChannelType::UInt8, 8},
            {ChannelSemantic::G, ChannelType::UInt8, 8},
            {ChannelSemantic::B, ChannelType::UInt8, 8},
            {ChannelSemantic::A, ChannelType::UInt8, 8}
        });
    }

    static PixelFormat Gray8()
    {
        return PixelFormat({
            {ChannelSemantic::Gray, ChannelType::UInt8, 8}
        });
    }

private:
    void validate()
    {
        if (m_channels.empty())
            throw std::runtime_error("PixelFormat: no channels");

        size_t offset = 0;
        for (const auto& c : m_channels)
        {
            if (c.bits == 0)
                throw std::runtime_error("PixelFormat: zero bit channel");
            offset += channelTypeSize(c.type);
        }

        if (offset == 0)
            throw std::runtime_error("PixelFormat: invalid pixel size");
    }

private:
    std::vector<ChannelDesc> m_channels;
};

} // namespace mylibImageReader
