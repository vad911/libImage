#pragma once

#include <vector>
#include <coreImage/channel.h>

namespace myCoreImage
{

// Тип для массива каналов
using ChannelArray = std::vector<Channel>;

// ============================
// fromInterleaved
// Создать массив каналов из interleaved изображения
// imageData   : поток байтов (interleaved)
// width,height: размеры изображения
// numChannels : количество каналов
// elementDescs: описания каналов (тип+битность)
// semantics   : семантика каналов (R,G,B,Gray,...)
// ============================
ChannelArray fromInterleaved(
    const std::vector<byte>& imageData,
    std::size_t width,
    std::size_t height,
    std::size_t numChannels,
    const std::vector<ChannelElementDesc>& elementDescs,
    const std::vector<ChannelSemantic>& semantics
);

// ============================
// toInterleaved
// Превратить массив каналов обратно в interleaved поток байтов
// ============================
std::vector<byte> toInterleaved(const ChannelArray& channels);

} // namespace myCoreImage
