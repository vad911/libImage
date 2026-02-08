#include <coreImage/transform.h>
#include <stdexcept>
#include <cmath>
#include <cstring>

namespace myCoreImage {
namespace transform {

Image resize(const Image& src, std::size_t newWidth, std::size_t newHeight)
{
    if(src.width() == 0 || src.height() == 0 || newWidth == 0 || newHeight == 0)
        throw std::runtime_error("Invalid dimensions for resize");

    Image dst(newWidth, newHeight, {}); // заполним каналы ниже

    // создаём копии каналов с теми же семантиками и типами
    std::vector<ChannelInfo> channelInfos;
    for(std::size_t c=0; c<src.numChannels(); ++c)
        channelInfos.push_back(src.channel(c).info());

    dst = Image(newWidth, newHeight, channelInfos);

    // простой nearest-neighbor resize
    for(std::size_t c=0; c<src.numChannels(); ++c)
    {
        const auto& srcChannel = src.channel(c);
        auto& dstChannel = dst.channel(c);

        for(std::size_t y=0; y<newHeight; ++y)
        {
            size_t srcY = y * src.height() / newHeight;
            for(std::size_t x=0; x<newWidth; ++x)
            {
                size_t srcX = x * src.width() / newWidth;
                dstChannel.data().at(x,y) = srcChannel.data().at(srcX, srcY);
            }
        }
    }

    return dst;
}

Image rotate(const Image& src, double angleDegrees)
{
    if(src.width() == 0 || src.height() == 0)
        throw std::runtime_error("Empty image");

    double angleRad = angleDegrees * M_PI / 180.0;
    double cosA = std::cos(angleRad);
    double sinA = std::sin(angleRad);

    // вычисляем размеры нового изображения
    std::size_t newWidth = static_cast<std::size_t>(std::ceil(src.width() * std::abs(cosA) + src.height() * std::abs(sinA)));
    std::size_t newHeight = static_cast<std::size_t>(std::ceil(src.width() * std::abs(sinA) + src.height() * std::abs(cosA)));

    std::vector<ChannelInfo> channelInfos;
    for(std::size_t c=0; c<src.numChannels(); ++c)
        channelInfos.push_back(src.channel(c).info());

    Image dst(newWidth, newHeight, channelInfos);

    // простой nearest-neighbor поворот вокруг центра
    double cx = src.width() / 2.0;
    double cy = src.height() / 2.0;
    double ncx = newWidth / 2.0;
    double ncy = newHeight / 2.0;

    for(std::size_t y=0; y<newHeight; ++y)
    {
        for(std::size_t x=0; x<newWidth; ++x)
        {
            double srcX =  cosA*(x-ncx) + sinA*(y-ncy) + cx;
            double srcY = -sinA*(x-ncx) + cosA*(y-ncy) + cy;

            int ix = static_cast<int>(std::round(srcX));
            int iy = static_cast<int>(std::round(srcY));

            if(ix>=0 && ix<int(src.width()) && iy>=0 && iy<int(src.height()))
            {
                for(std::size_t c=0; c<src.numChannels(); ++c)
                {
                    dst.channel(c).data().at(x,y) = src.channel(c).data().at(ix,iy);
                }
            }
        }
    }

    return dst;
}

} // namespace transform
} // namespace myCoreImage
