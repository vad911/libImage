#include <imageReader/channelView.h>
#include <cstring>
#include <algorithm>

namespace mylibImageReader
{

ChannelView::ChannelView(byte* d, ChannelType t, ChannelSize s)
    : m_data(d), m_type(t), m_size(s)
{
}

double ChannelView::get() const
{
    if (m_type == ChannelType::UInt && m_size == ChannelSize::Bit8)
        return *m_data / 255.0;

    if (m_type == ChannelType::UInt && m_size == ChannelSize::Bit16)
    {
        uint16_t v;
        std::memcpy(&v, m_data, 2);
        return v / 65535.0;
    }

    if (m_type == ChannelType::Float)
        return *reinterpret_cast<float*>(m_data);

    if (m_type == ChannelType::Double)
        return *reinterpret_cast<double*>(m_data);

    return 0.0;
}

void ChannelView::set(double v)
{
    v = std::clamp(v, 0.0, 1.0);

    if (m_type == ChannelType::UInt && m_size == ChannelSize::Bit8)
        *m_data = static_cast<byte>(v * 255.0);
    else if (m_type == ChannelType::UInt && m_size == ChannelSize::Bit16)
    {
        uint16_t t = static_cast<uint16_t>(v * 65535.0);
        std::memcpy(m_data, &t, 2);
    }
    else if (m_type == ChannelType::Float)
        *reinterpret_cast<float*>(m_data) = static_cast<float>(v);
    else if (m_type == ChannelType::Double)
        *reinterpret_cast<double*>(m_data) = v;
}

}
