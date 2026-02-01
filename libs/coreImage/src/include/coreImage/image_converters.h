#pragma once

#include <coreImage/lib_coreImage.h>
#include <coreImage/channel.h>
#include <coreImage/types.h> 

#include <vector>

namespace myCoreImage
{

namespace converters 
{

using ChannelArray = std::vector<Channel>;

class Image; // forward declaration

// ============================
// Планар <-> Interleaved
// ============================
ChannelArray COREIMAGE_API fromInterleaved(
    const std::vector<byte>& imageData,
    std::size_t width,
    std::size_t height,
    std::size_t numChannels,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
);

std::vector<byte> COREIMAGE_API toInterleaved(const ChannelArray& channels);


// Объявление функции, реализация в image.cpp
Image COREIMAGE_API fromPacked(
    const std::vector<byte>& src,
    std::size_t width,
    std::size_t height,
    PixelFormat format
);
} // -- namespace converters

} // namespace myCoreImage
