#include <coreImage/channelView.h>
#include <cstring>

namespace myCoreImage
{
ChannelView::ChannelView(void* data,std::size_t width,std::size_t height,std::size_t strideBytes,ChannelElementDesc elementDesc)
    : m_data(static_cast<byte*>(data)), m_width(width), m_height(height), m_strideBytes(strideBytes), m_elementDesc(elementDesc) {}

void* ChannelView::data() const noexcept { return m_data; }
std::size_t ChannelView::width() const noexcept { return m_width; }
std::size_t ChannelView::height() const noexcept { return m_height; }
std::size_t ChannelView::strideBytes() const noexcept { return m_strideBytes; }
ChannelElementDesc ChannelView::elementDesc() const noexcept { return m_elementDesc; }
std::size_t ChannelView::bytesPerElement() const noexcept { return m_elementDesc.bytesPerElement(); }
ChannelView ChannelView::subView(std::size_t x,std::size_t y,std::size_t w,std::size_t h) const
{
    byte* offset = m_data + y*m_strideBytes + x*bytesPerElement();
    return ChannelView(offset,w,h,m_strideBytes,m_elementDesc);
}
} // namespace myCoreImage
