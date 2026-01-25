#pragma once

#include <vector>
#include <coreImage/channel.h>

namespace myCoreImage
{

// Тип для массива каналов
using ChannelArray = std::vector<Channel>;

// Создать массив каналов из interleaved изображения
ChannelArray fromInterleaved(
    const std::vector<byte>& imageData, // поток байтов
    std::size_t width,
    std::size_t height,
    std::size_t numChannels,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
);

// Превратить массив каналов обратно в interleaved поток байтов
std::vector<byte> toInterleaved(
    const ChannelArray& channels
);

} // namespace myCoreImage
