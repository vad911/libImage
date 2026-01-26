#pragma once

#include <coreImage/lib_coreImage.h>
#include <coreImage/types.h>
#include <coreImage/channelElementDesc.h>

#include <cstddef>


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
    ChannelSemantic     m_semantic{ ChannelSemantic::Unknown };  // -- отвечает на вопрос: что это за канал R / G / B / Alpha / Gray / BW
    ChannelElementDesc  m_elementDesc{};                         // -- отвечает на вопрос: как он хранится в памяти : тип (int/float), битность (1/8/16/32/64)
};

} // namespace myCoreImage

