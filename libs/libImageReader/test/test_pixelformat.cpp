#include <imageReader/pixelFormat.h>
#include <cassert>

using namespace mylibImageReader;

int main()
{
    PixelFormat rgb = PixelFormat::RGB8();
    PixelFormat rgba = PixelFormat::RGBA8();

    assert(rgb.channelCount() == 3);
    assert(!rgb.hasAlpha());

    assert(rgba.channelCount() == 4);
    assert(rgba.hasAlpha());

    return 0;
}
