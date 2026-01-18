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

    // Alpha handling rule:
    // If format has no alpha channel, alpha is assumed to be 1.0
    double alpha() const;

private:
    byte* m_data;
    const PixelFormat& m_fmt;
};

}
