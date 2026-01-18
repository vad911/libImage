#include <imageReader/pixelConverter.h>
#include <imageReader/pixelView.h>
#include <imageReader/GammaLUT.h>
#include <algorithm>
#include <cmath>

namespace mylibImageReader
{

static void gray_to_rgb(PixelView& s, PixelView& d)
{
    double g = s.channel(0).get();
    d.channel(0).set(g);
    d.channel(1).set(g);
    d.channel(2).set(g);
}

static void rgb_to_gray(PixelView& s, PixelView& d)
{
    double r = s.channel(0).get();
    double g = s.channel(1).get();
    double b = s.channel(2).get();
    d.channel(0).set(0.299*r + 0.587*g + 0.114*b);
}

// --- Lab / LCh / RGB ---

static constexpr double Xn = 0.95047;
static constexpr double Yn = 1.00000;
static constexpr double Zn = 1.08883;

static double f(double t)
{
    return t > 0.008856 ? std::cbrt(t) : (7.787 * t + 16.0 / 116.0);
}

static double finv(double t)
{
    double t3 = t * t * t;
    return t3 > 0.008856 ? t3 : (t - 16.0 / 116.0) / 7.787;
}

static void rgb_to_lab(PixelView& s, PixelView& d)
{
    double r = GammaLUT::srgbToLinear(s.channel(0).get());
    double g = GammaLUT::srgbToLinear(s.channel(1).get());
    double b = GammaLUT::srgbToLinear(s.channel(2).get());

    double X = 0.4124*r + 0.3576*g + 0.1805*b;
    double Y = 0.2126*r + 0.7152*g + 0.0722*b;
    double Z = 0.0193*r + 0.1192*g + 0.9505*b;

    double fx = f(X / Xn);
    double fy = f(Y / Yn);
    double fz = f(Z / Zn);

    d.channel(0).set((116*fy - 16) / 100.0);
    d.channel(1).set((500*(fx-fy) + 128) / 255.0);
    d.channel(2).set((200*(fy-fz) + 128) / 255.0);
}

static void lab_to_rgb(PixelView& s, PixelView& d)
{
    double L = s.channel(0).get() * 100.0;
    double a = s.channel(1).get() * 255.0 - 128;
    double b = s.channel(2).get() * 255.0 - 128;

    double fy = (L + 16) / 116.0;
    double fx = fy + a / 500.0;
    double fz = fy - b / 200.0;

    double X = Xn * finv(fx);
    double Y = Yn * finv(fy);
    double Z = Zn * finv(fz);

    double r =  3.2406*X -1.5372*Y -0.4986*Z;
    double g = -0.9689*X +1.8758*Y +0.0415*Z;
    double bl = 0.0557*X -0.2040*Y +1.0570*Z;

    d.channel(0).set(GammaLUT::linearToSrgb(r));
    d.channel(1).set(GammaLUT::linearToSrgb(g));
    d.channel(2).set(GammaLUT::linearToSrgb(bl));
}

static void lab_to_lch(PixelView& s, PixelView& d)
{
    double L = s.channel(0).get();
    double a = s.channel(1).get()*255.0 - 128;
    double b = s.channel(2).get()*255.0 - 128;

    double C = std::sqrt(a*a + b*b);
    double H = std::atan2(b, a) / (2*M_PI);
    if (H < 0) H += 1.0;

    d.channel(0).set(L);
    d.channel(1).set(C / 128.0);
    d.channel(2).set(H);
}

static void lch_to_lab(PixelView& s, PixelView& d)
{
    double L = s.channel(0).get();
    double C = s.channel(1).get() * 128.0;
    double H = s.channel(2).get() * 2*M_PI;

    double a = C * std::cos(H);
    double b = C * std::sin(H);

    d.channel(0).set(L);
    d.channel(1).set((a + 128) / 255.0);
    d.channel(2).set((b + 128) / 255.0);
}

bool PixelConverter::convertImage(const ImageCommon& src, ImageCommon& dst)
{
    if (src.width != dst.width || src.height != dst.height)
        return false;

    for (int y = 0; y < src.height; ++y)
    {
        for (int x = 0; x < src.width; ++x)
        {
            byte* sp = const_cast<byte*>(src.data.data() +
                y * src.stride() + x * src.format.bytesPerPixel());
            byte* dp = dst.data.data() +
                y * dst.stride() + x * dst.format.bytesPerPixel();

            PixelView ps(sp, src.format);
            PixelView pd(dp, dst.format);

            if (src.format.layout == ChannelLayout::Y &&
                dst.format.layout == ChannelLayout::RGB)
                gray_to_rgb(ps, pd);
            else if (src.format.layout == ChannelLayout::RGB &&
                     dst.format.layout == ChannelLayout::Y)
                rgb_to_gray(ps, pd);
            else if (src.format.layout == ChannelLayout::RGB &&
                     dst.format.layout == ChannelLayout::Lab)
                rgb_to_lab(ps, pd);
            else if (src.format.layout == ChannelLayout::Lab &&
                     dst.format.layout == ChannelLayout::RGB)
                lab_to_rgb(ps, pd);
            else if (src.format.layout == ChannelLayout::Lab &&
                     dst.format.layout == ChannelLayout::LCh)
                lab_to_lch(ps, pd);
            else if (src.format.layout == ChannelLayout::LCh &&
                     dst.format.layout == ChannelLayout::Lab)
                lch_to_lab(ps, pd);
        }
    }
    return true;
}

}
