#pragma once

#include <coreImage/lib_coreImage.h>
#include <coreImage/types.h>
#include <coreImage/channelElementDesc.h>

namespace myCoreImage
{

class COREIMAGE_API ChannelInfo
{
public:
    ChannelInfo() = default;

    ChannelInfo(ChannelSemantic semantic,
                ChannelElementDesc elementDesc);

    ChannelSemantic semantic() const noexcept;
    ChannelElementDesc elementDesc() const noexcept;

private:
    ChannelSemantic     m_semantic{ ChannelSemantic::Unknown };
    ChannelElementDesc m_elementDesc{};
};

} // namespace myCoreImage

