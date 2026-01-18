#include <imageReader/conversionPipeline.h>
#include <cassert>

using namespace mylibImageReader;

int main()
{
    ImageCommon img;
    img.width = 1;
    img.height = 1;
    img.format = {
        ColorSpace::RGB,
        ChannelLayout::RGB,
        ChannelType::UInt,
        ChannelSize::Bit8,
        PixelPacking::None
    };
    img.data = {255, 0, 0};

    ImageCommon out;
    PixelFormat hsv{
        ColorSpace::HSV,
        ChannelLayout::HSV,
        ChannelType::UInt,
        ChannelSize::Bit8,
        PixelPacking::None
    };

    bool ok = convert(img).to(hsv).run(out);
    assert(ok);
}
