#pragma once
#include <coreImage/lib_coreImage.h>
#include <coreImage/channel.h>
#include <coreImage/coreImage.h>
#include <vector>
#include <cstddef>

namespace myCoreImage
{

    namespace mci = myCoreImage;

class COREIMAGE_API Image
{
public:
    Image() = default;
    Image(std::size_t width, std::size_t height, const std::vector<ChannelInfo>& channelInfos);

    std::size_t width() const { return m_width; }
    std::size_t height() const { return m_height; }
    std::size_t numChannels() const { return m_channels.size(); }

    Channel& channel(std::size_t index);
    const Channel& channel(std::size_t index) const;

    const ChannelArray& channels() const { return m_channels; }

    // Создание Image из interleaved потока байтов
    static Image fromInterleaved(
        const std::vector<byte>& imageData,
        std::size_t width,
        std::size_t height,
        const std::vector<ChannelElementDesc>& elementDescs,
        const std::vector<ChannelSemantic>& semantics
    );

    // Превращение Image обратно в interleaved поток байтов
    std::vector<byte> toInterleaved() const;

private:
    std::size_t m_width{0};
    std::size_t m_height{0};
    mci::ChannelArray m_channels;
};

// ============================
// ImageView
// ============================
class COREIMAGE_API ImageView
{
public:
    ImageView(Image& image);

    std::size_t width() const { return m_image.width(); }
    std::size_t height() const { return m_image.height(); }
    std::size_t numChannels() const { return m_image.numChannels(); }

    ChannelView channelView(std::size_t index);

private:
    Image& m_image;
};

} // namespace myCoreImage
