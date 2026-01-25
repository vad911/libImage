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
    switch (m_type)
    {
        case ChannelType::UInt8:
        {
            return static_cast<double>(*m_data) / 255.0;
        }

        case ChannelType::UInt16:
        {
            uint16_t v;
            std::memcpy(&v, m_data, sizeof(v));
            return static_cast<double>(v) / 65535.0;
        }

        case ChannelType::UInt32:
        {
            uint32_t v;
            std::memcpy(&v, m_data, sizeof(v));
            return static_cast<double>(v) / 4294967295.0;
        }

        case ChannelType::Float32:
        {
            float v;
            std::memcpy(&v, m_data, sizeof(v));
            return static_cast<double>(v);
        }

        case ChannelType::Float64:
        {
            double v;
            std::memcpy(&v, m_data, sizeof(v));
            return v;
        }
    }

    return 0.0; // unreachable, но пусть будет
}
void ChannelView::set(double v)
{
    v = std::clamp(v, 0.0, 1.0);

    switch (m_type)
    {
        case ChannelType::UInt8:
        {
            *m_data = static_cast<byte>(v * 255.0 + 0.5);
            break;
        }

        case ChannelType::UInt16:
        {
            uint16_t t = static_cast<uint16_t>(v * 65535.0 + 0.5);
            std::memcpy(m_data, &t, sizeof(t));
            break;
        }

        case ChannelType::UInt32:
        {
            uint32_t t = static_cast<uint32_t>(v * 4294967295.0 + 0.5);
            std::memcpy(m_data, &t, sizeof(t));
            break;
        }

        case ChannelType::Float32:
        {
            float t = static_cast<float>(v);
            std::memcpy(m_data, &t, sizeof(t));
            break;
        }

        case ChannelType::Float64:
        {
            double t = v;
            std::memcpy(m_data, &t, sizeof(t));
            break;
        }
    }
}
}
