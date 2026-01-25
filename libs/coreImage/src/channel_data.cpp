#include <coreImage/channel_data.h>

#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace myCoreImage
{
    ChannelData::ChannelData(const ChannelInfo& info,
                             std::size_t elementCount)
        : m_info(info)
        , m_count(elementCount)
    {
        const std::size_t bytes =
            elementCount * info.element.bytes();

        m_data = static_cast<std::byte*>(::operator new(bytes));
        std::memset(m_data, 0, bytes);
    }

    ChannelData::~ChannelData()
    {
        ::operator delete(m_data);
    }

    ChannelData::ChannelData(ChannelData&& other) noexcept
    {
        *this = std::move(other);
    }

    ChannelData& ChannelData::operator=(ChannelData&& other) noexcept
    {
        if (this != &other)
        {
            ::operator delete(m_data);

            m_info  = other.m_info;
            m_data  = other.m_data;
            m_count = other.m_count;

            other.m_data  = nullptr;
            other.m_count = 0;
        }
        return *this;
    }

    void* ChannelData::data() noexcept
    {
        return m_data;
    }

    const void* ChannelData::data() const noexcept
    {
        return m_data;
    }

    std::size_t ChannelData::elementCount() const noexcept
    {
        return m_count;
    }

    std::size_t ChannelData::bytesPerElement() const noexcept
    {
        return m_info.element.bytes();
    }

    std::size_t ChannelData::totalBytes() const noexcept
    {
        return m_count * bytesPerElement();
    }

    const ChannelInfo& ChannelData::info() const noexcept
    {
        return m_info;
    }

    // ─────────────────────────────────────────────
    // Internal template implementation
    // ─────────────────────────────────────────────
    template<typename T>
    static void normalizeImpl(T* data, std::size_t count)
    {
        if (count == 0) return;

        auto [minIt, maxIt] = std::minmax_element(data, data + count);
        T minVal = *minIt;
        T maxVal = *maxIt;

        if (minVal == maxVal) return;

        for (std::size_t i = 0; i < count; ++i)
        {
            data[i] = (data[i] - minVal) / (maxVal - minVal);
        }
    }

    // ─────────────────────────────────────────────
    // Public runtime dispatch
    // ─────────────────────────────────────────────
    void normalize(ChannelData& data)
    {
        const auto& elem = data.info().element;

        if (!elem.isFloat())
        {
            throw std::runtime_error(
                "normalize: only float channels supported");
        }

        switch (elem.bitDepth)
        {
            case ChannelBitDepth::Bit32:
                normalizeImpl(
                    static_cast<float*>(data.data()),
                    data.elementCount());
                break;

            case ChannelBitDepth::Bit64:
                normalizeImpl(
                    static_cast<double*>(data.data()),
                    data.elementCount());
                break;

            default:
                throw std::runtime_error(
                    "normalize: unsupported bit depth");
        }
    }
}
