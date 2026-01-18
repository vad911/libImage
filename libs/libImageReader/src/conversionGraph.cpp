#include <imageReader/conversionGraph.h>

namespace mylibImageReader
{

PixelFormat ConversionGraph::canonicalRGB()
{
    return PixelFormat{
        ColorSpace::RGB,
        ChannelLayout::RGB,
        ChannelType::Float,
        ChannelSize::Bit32,
        PixelPacking::None
    };
}

std::vector<PixelFormat>
ConversionGraph::buildPath(const PixelFormat& src,
                           const PixelFormat& dst)
{
    if (src.colorSpace == dst.colorSpace)
        return { dst };

    PixelFormat canon = canonicalRGB();
    std::vector<PixelFormat> path;

    if (src.colorSpace != ColorSpace::RGB)
        path.push_back(canon);

    path.push_back(dst);
    return path;
}

}
