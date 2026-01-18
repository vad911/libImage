#pragma once
#include <cstddef>
#include <imageReader/channelView.h>

namespace mylibImageReader
{
class PixelView
{
public:
    PixelView(byte* data, const PixelFormat& fmt);

    ChannelView channel(size_t idx);
    ChannelView channel(size_t idx) const;

    double alpha() const;

private:
    byte* m_data;
    const PixelFormat& m_fmt;
};

}
