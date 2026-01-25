#pragma once

#include <coreImage/types.h>

namespace myCoreImage
{
    struct ChannelInfo
    {
        ChannelSemantic    semantic{ChannelSemantic::Undefined};
        ChannelElementDesc element{};
    };
}
