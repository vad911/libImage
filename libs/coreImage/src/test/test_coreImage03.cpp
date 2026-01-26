#include <coreImage/image.h>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace myCoreImage;

int main()
{
    std::cout << "=== Test CoreImage 0.0.1 ===\n";

    // ------------------------------
    // 1. RGB565 2x2
    // ------------------------------
    std::cout << "\n1) RGB565 2x2\n";
    std::vector<uint16_t> rgb565Pixels = { 0xF800, 0x07E0, 0x001F, 0xFFFF }; // R,G,B,F
    std::vector<byte> packedRgb565(reinterpret_cast<byte*>(rgb565Pixels.data()),
                                   reinterpret_cast<byte*>(rgb565Pixels.data()) + rgb565Pixels.size()*2);

    Image imgRgb = Image::from_packed(packedRgb565, 2, 2, PixelFormat::RGB565);

    for (size_t c = 0; c < imgRgb.numChannels(); ++c)
    {
        auto cv = imgRgb.channel(c).view();
        auto* data = static_cast<byte*>(cv.data());
        std::cout << "Channel " << c << ": ";
        for (size_t i = 0; i < imgRgb.width()*imgRgb.height(); ++i)
            std::cout << +data[i] << " ";
        std::cout << "\n";
    }

    // ------------------------------
    // 2. BW1 8x1
    // ------------------------------
    std::cout << "\n2) BW1 8x1\n";
    std::vector<byte> bwPacked = { 0b10110011 }; // 8 пикселей в 1 байте
    Image imgBW = Image::from_packed(bwPacked, 8, 1, PixelFormat::BW1);

    auto* grayData = static_cast<byte*>(imgBW.channel(0).data().data());
    std::cout << "Gray channel: ";
    for (size_t i = 0; i < 8; ++i)
        std::cout << +grayData[i] << " ";
    std::cout << "\n";

    // ------------------------------
    // 3. Interleaved RGB 2x2
    // ------------------------------
    std::cout << "\n3) Interleaved RGB 2x2\n";
    std::vector<byte> interleavedRGB = { 10,20,30, 40,50,60, 70,80,90, 100,110,120 };
    std::vector<ChannelElementDesc> rgbDescs = {
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 }
    };
    std::vector<ChannelSemantic> rgbSemantics = { ChannelSemantic::Red, ChannelSemantic::Green, ChannelSemantic::Blue };

    Image imgInterleaved = Image::fromInterleaved(interleavedRGB, 2, 2, rgbDescs, rgbSemantics);
    ImageView view(imgInterleaved);

    for (size_t c = 0; c < imgInterleaved.numChannels(); ++c)
    {
        auto cv = view.channelView(c);
        auto* data = static_cast<byte*>(cv.data());
        std::cout << "Channel " << c << ": ";
        for (size_t i = 0; i < imgInterleaved.width()*imgInterleaved.height(); ++i)
            std::cout << +data[i] << " ";
        std::cout << "\n";
    }

    // ------------------------------
    // 4. Convert planar back to interleaved
    // ------------------------------
    std::cout << "\n4) Planar -> Interleaved\n";
    std::vector<byte> interleavedOut = toInterleaved(imgInterleaved.channels());
    for (size_t i = 0; i < interleavedOut.size(); i += 3)
    {
        std::cout << "Pixel: " 
                  << +interleavedOut[i] << " "
                  << +interleavedOut[i+1] << " "
                  << +interleavedOut[i+2] << "\n";
    }

    return 0;
}
