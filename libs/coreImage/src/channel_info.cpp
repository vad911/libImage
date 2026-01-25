#include <coreImage/channel_info.h>

namespace myCoreImage
{

ChannelInfo::ChannelInfo(ChannelSemantic semantic,
                         ChannelElementDesc elementDesc)
    : m_semantic(semantic)
    , m_elementDesc(elementDesc)
{
}

ChannelSemantic ChannelInfo::semantic() const noexcept
{
    return m_semantic;
}

ChannelElementDesc ChannelInfo::elementDesc() const noexcept
{
    return m_elementDesc;
}

} // namespace myCoreImage
