#include <imageReader/conversionGraph.h>

namespace mylibImageReader
{



PixelFormat ConversionGraph::canonicalRGB()
{
    return PixelFormat({
        ChannelDesc{ ChannelSemantic::R, ChannelType::Float32, ChannelSize::Bits32 },
        ChannelDesc{ ChannelSemantic::G, ChannelType::Float32, ChannelSize::Bits32 },
        ChannelDesc{ ChannelSemantic::B, ChannelType::Float32, ChannelSize::Bits32 }
    });
}


std::vector<PixelFormat> ConversionGraph::buildPath(const PixelFormat& src,
                                                    const PixelFormat& dst)
{
    if (src.colorSpace() == dst.colorSpace())
    return { dst };


    PixelFormat canon = canonicalRGB();
    std::vector<PixelFormat> path;

    if (src.colorSpace() != ColorSpace::RGB)
        path.push_back(canon);

    path.push_back(dst);
    return path;
}

}
