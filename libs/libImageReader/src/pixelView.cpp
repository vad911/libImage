#include <imageReader/pixelView.h>

namespace mylibImageReader
{

PixelView::PixelView(byte* d, const PixelFormat& f)
    : m_data(d), m_fmt(f)
{
}

ChannelView PixelView::channel(size_t idx)
{
    size_t offset = idx * (static_cast<byte>(m_fmt.channelSize) / 8);
    return ChannelView(m_data + offset, m_fmt.channelType, m_fmt.channelSize);
}

double PixelView::alpha() const
{
    if (!m_fmt.hasAlpha())
        return 1.0;

    return channel(m_fmt.channels() - 1).get();
}

}
