#pragma once
#include <imageReader/pixelFormat.h>

namespace mylibImageReader
{

class ChannelView
{
public:
    ChannelView(byte* data,
                ChannelType type,
                ChannelSize size);

    double get() const;
    void set(double v);

private:
    byte*       m_data;
    ChannelType m_type;
    ChannelSize m_size;
};

}
