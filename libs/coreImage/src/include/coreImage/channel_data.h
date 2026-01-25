#pragma once

#include <cstddef>
#include <coreImage/channel_info.h>

namespace myCoreImage
{
    class ChannelData
    {
    public:
        ChannelData() = default;

        ChannelData(const ChannelInfo& info,
                    std::size_t elementCount);

        ~ChannelData();

        ChannelData(const ChannelData&) = delete;
        ChannelData& operator=(const ChannelData&) = delete;

        ChannelData(ChannelData&&) noexcept;
        ChannelData& operator=(ChannelData&&) noexcept;

        void*       data()       noexcept;
        const void* data() const noexcept;

        std::size_t elementCount() const noexcept;
        std::size_t bytesPerElement() const noexcept;
        std::size_t totalBytes() const noexcept;

        const ChannelInfo& info() const noexcept;

    private:
        ChannelInfo m_info{};
        std::byte*  m_data  = nullptr;
        std::size_t m_count = 0;
    };

    // Example algorithm
    void normalize(ChannelData& data);
}
