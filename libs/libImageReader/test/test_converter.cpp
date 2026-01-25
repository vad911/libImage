
#include <imageReader/conversionPipeline.h>
#include <cassert>

using namespace mylibImageReader;

int main()
{
    ImageCommon img;
    img.width = 1;
    img.height = 1;
    img.format = PixelFormat (
        ColorSpace::Gray,
        ChannelLayout::Y,
        ChannelType::UInt,
        ChannelSize::Bit8,
        PixelPacking::None
        );
    img.data = {128};

    ImageCommon out;
    PixelFormat rgb{
        ColorSpace::RGB,
        ChannelLayout::RGB,
        ChannelType::UInt,
        ChannelSize::Bit8,
        PixelPacking::None
    };

    bool ok = convert(img).to(rgb).run(out);
    assert(ok);
}
