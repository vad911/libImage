#include <coreImage/image.h>
#include <iostream>

namespace mci = myCoreImage;

int main()
{
    // Простейший interleaved RGB 2x2
    std::vector<mci::byte> interleaved = {10,20,30, 40,50,60, 70,80,90, 100,110,120};
    
    std::vector<mci::ChannelElementDesc> descs = {
        { mci::ChannelDataType::UnsignedInt, mci::ChannelBitDepth::Bit8 },
        { mci::ChannelDataType::UnsignedInt, mci::ChannelBitDepth::Bit8 },
        { mci::ChannelDataType::UnsignedInt, mci::ChannelBitDepth::Bit8 }
    };

    std::vector<mci::ChannelSemantic> semantics = {
        mci::ChannelSemantic::Red,
        mci::ChannelSemantic::Green,
        mci::ChannelSemantic::Blue
    };

    mci::Image img = mci::Image::fromInterleaved(interleaved, 2, 2, descs, semantics);
    mci::ImageView view(img);

    for (std::size_t c = 0; c < img.numChannels(); ++c)
    {
        auto cv = view.channelView(c);
        auto data = static_cast<mci::byte*>(cv.data());
        std::cout << "Channel " << c << ": ";
        for (std::size_t i = 0; i < img.width()*img.height(); ++i)
            std::cout << +data[i] << " ";
        std::cout << "\n";
    }

    auto interleaved_out = img.toInterleaved();
    std::cout << "Interleaved output: ";
    for (auto b : interleaved_out) std::cout << +b << " ";
    std::cout << "\n";

    return 0;
}
