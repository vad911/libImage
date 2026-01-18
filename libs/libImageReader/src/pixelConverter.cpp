#include <imageReader/pixelConverter.h>
#include <imageReader/pixelView.h>
#include <cmath>
#include <algorithm>

namespace mylibImageReader
{

static void rgb_to_hsv(PixelView& s, PixelView& d)
{
    double r = s.channel(0).get();
    double g = s.channel(1).get();
    double b = s.channel(2).get();

    double maxv = std::max({r, g, b});
    double minv = std::min({r, g, b});
    double delta = maxv - minv;

    double h = 0.0;
    if (delta > 0.0)
    {
        if (maxv == r) h = fmod((g - b) / delta, 6.0);
        else if (maxv == g) h = (b - r) / delta + 2.0;
        else h = (r - g) / delta + 4.0;

        h /= 6.0;
        if (h < 0) h += 1.0;
    }

    double s_v = (maxv == 0.0) ? 0.0 : delta / maxv;

    d.channel(0).set(h);
    d.channel(1).set(s_v);
    d.channel(2).set(maxv);
}

bool PixelConverter::convertImage(const ImageCommon& src, ImageCommon& dst)
{
    if (src.width != dst.width || src.height != dst.height)
        return false;

    for (int y = 0; y < src.height; ++y)
    {
        byte* sp = const_cast<byte*>(src.data.data() + y * src.stride());
        byte* dp = dst.data.data() + y * dst.stride();

        for (int x = 0; x < src.width; ++x)
        {
            PixelView ps(sp + x * src.format.bytesPerPixel(), src.format);
            PixelView pd(dp + x * dst.format.bytesPerPixel(), dst.format);

            if (src.format.layout == ChannelLayout::RGB &&
                dst.format.layout == ChannelLayout::HSV)
            {
                rgb_to_hsv(ps, pd);

                if (dst.format.hasAlpha())
                    pd.channel(dst.format.channels() - 1).set(ps.alpha());
            }
        }
    }
    return true;
}

}
