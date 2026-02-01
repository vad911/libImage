#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

#include <coreImage/image_converter.h>

using namespace myCoreImage;

int main()
{
    // =========================
    // 1. RGB 2x2, uint8
    // =========================
    std::size_t width = 2, height = 2;
    std::vector<byte> interleavedRGB = { 10,20,30, 40,50,60, 70,80,90, 100,110,120 };

    std::vector<ChannelElementDesc> rgbDescs = {
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 }
    };
    std::vector<ChannelSemantic> rgbSemantics = { ChannelSemantic::Red, ChannelSemantic::Green, ChannelSemantic::Blue };

    ChannelArray rgbChannels = fromInterleaved(interleavedRGB, width, height, 3, rgbDescs, rgbSemantics);

    std::cout << "RGB Planar channels:\n";
    for (std::size_t c = 0; c < rgbChannels.size(); ++c)
    {
        auto& data = rgbChannels[c].data();
        byte* ptr = static_cast<byte*>(data.data());
        std::cout << "Channel " << static_cast<int>(rgbSemantics[c]) << ": ";
        for (std::size_t i = 0; i < width*height; ++i) std::cout << +ptr[i] << " ";
        std::cout << "\n";
    }

    // =========================
    // 2. RGBA 2x2, uint8
    // =========================
    std::vector<byte> interleavedRGBA = {
        1,2,3,4,   5,6,7,8,   9,10,11,12, 13,14,15,16
    };

    std::vector<ChannelElementDesc> rgbaDescs = {
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 },
        { ChannelDataType::UnsignedInt, ChannelBitDepth::Bit8 }
    };
    std::vector<ChannelSemantic> rgbaSemantics = {
        ChannelSemantic::Red, ChannelSemantic::Green,
        ChannelSemantic::Blue, ChannelSemantic::Alpha
    };

    ChannelArray rgbaChannels = fromInterleaved(interleavedRGBA, width, height, 4, rgbaDescs, rgbaSemantics);

    std::cout << "\nRGBA Planar channels:\n";
    for (std::size_t c = 0; c < rgbaChannels.size(); ++c)
    {
        auto& data = rgbaChannels[c].data();
        byte* ptr = static_cast<byte*>(data.data());
        std::cout << "Channel " << static_cast<int>(rgbaSemantics[c]) << ": ";
        for (std::size_t i = 0; i < width*height; ++i) std::cout << +ptr[i] << " ";
        std::cout << "\n";
    }

    // =========================
    // 3. Gray 2x2, float32
    // =========================
    std::vector<float> interleavedGray = {0.1f,0.2f,0.3f,0.4f};
    std::vector<byte> grayBytes(interleavedGray.size()*sizeof(float));
    std::memcpy(grayBytes.data(), interleavedGray.data(), grayBytes.size());

    ChannelElementDesc grayDesc{ ChannelDataType::Float, ChannelBitDepth::Bit32 };
    ChannelInfo grayInfo(ChannelSemantic::Gray, grayDesc);
    Channel grayChannel(grayInfo, width, height);

    ChannelView grayView(grayChannel.data().data(), width, height, grayChannel.data().strideBytes(), grayDesc);
    std::memcpy(grayView.data(), grayBytes.data(), grayBytes.size());

    std::cout << "\nGray float32 channel planar:\n";
    for (std::size_t y=0;y<grayView.height();++y)
    {
        for (std::size_t x=0;x<grayView.width();++x)
        {
            float* ptr = reinterpret_cast<float*>(static_cast<byte*>(grayView.data()) + y*grayView.strideBytes() + x*grayView.bytesPerElement());
            std::cout << *ptr << " ";
        }
        std::cout << "\n";
    }

    // =========================
    // 4. Gray16 (BW16), uint16
    // =========================
    std::vector<uint16_t> interleavedGray16 = {1000,2000,3000,4000};
    std::vector<byte> gray16Bytes(interleavedGray16.size()*sizeof(uint16_t));
    std::memcpy(gray16Bytes.data(), interleavedGray16.data(), gray16Bytes.size());

    ChannelElementDesc gray16Desc{ ChannelDataType::UnsignedInt, ChannelBitDepth::Bit16 };
    ChannelInfo gray16Info(ChannelSemantic::BlackWhite, gray16Desc);
    Channel gray16Channel(gray16Info, width, height);

    ChannelView gray16View(gray16Channel.data().data(), width, height, gray16Channel.data().strideBytes(), gray16Desc);
    std::memcpy(gray16View.data(), gray16Bytes.data(), gray16Bytes.size());

    std::cout << "\nGray16 channel planar:\n";
    for (std::size_t y=0;y<gray16View.height();++y)
    {
        for (std::size_t x=0;x<gray16View.width();++x)
        {
            uint16_t* ptr = reinterpret_cast<uint16_t*>(static_cast<byte*>(gray16View.data()) + y*gray16View.strideBytes() + x*gray16View.bytesPerElement());
            std::cout << *ptr << " ";
        }
        std::cout << "\n";
    }

    // =========================
    // 5. Используем ChannelView для изменения R-канала RGB
    // =========================
    ChannelView redView = rgbChannels[0].view();
    for (std::size_t y=0;y<redView.height();++y)
        for (std::size_t x=0;x<redView.width();++x)
        {
            byte* ptr = static_cast<byte*>(redView.data()) + y*redView.strideBytes() + x*redView.bytesPerElement();
            *ptr += 1;
        }

    std::cout << "\nRGB Red channel after increment:\n";
    for (std::size_t y=0;y<redView.height();++y)
    {
        for (std::size_t x=0;x<redView.width();++x)
        {
            byte* ptr = static_cast<byte*>(redView.data()) + y*redView.strideBytes() + x*redView.bytesPerElement();
            std::cout << +(*ptr) << " ";
        }
        std::cout << "\n";
    }

    // =========================
    // 6. Planar -> Interleaved back
    // =========================
    std::vector<byte> backInterleavedRGB = toInterleaved(rgbChannels);
    std::cout << "\nBack to interleaved RGB:\n";
    for (std::size_t i=0;i<backInterleavedRGB.size();i+=3)
    {
        std::cout << "Pixel: ";
        std::cout << +backInterleavedRGB[i] << " ";
        std::cout << +backInterleavedRGB[i+1] << " ";
        std::cout << +backInterleavedRGB[i+2] << "\n";
    }

    return 0;
}
