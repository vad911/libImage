#include <imageReader/pixelFormat.h>
#include <cassert>

using namespace mylibImageReader;

int main()
{
    PixelFormat f{
        ColorSpace::RGB,
        ChannelLayout::RGBA,
        ChannelType::UInt,
        ChannelSize::Bit8,
        PixelPacking::None
    };

    assert(f.channels() == 4);
    assert(f.bytesPerPixel() == 4);
    assert(f.hasAlpha());
}
