#ifndef IMAGECOMMON_H
#define IMAGECOMMON_H

// -------------------------------------------------------
// -- файл картинки промежуточный общий - в него конвертируются все форматы --
// -- и из него создаются все

#include <imageReader/types.h>
#include <vector>

struct ImageCommonHeader {
    types::PixelFormat pixelFormat;
    size_t width;     // -- размер в пикселях
    size_t height;    // -- размер в пикселях
    void clear();
};



class ImageCommon
{
public:
    ImageCommon();
    size_t getSize();

    void constructNewImageCommon(const ImageCommonHeader& header, const std::vector<types::byte>& data);
    void setHeader(const ImageCommonHeader& header);
    void setData(const std::vector<types::byte>& data);

    // -- numberRow = [0... (height-1)]
    std::vector<types::byte> getRow(size_t numberRow);
    std::vector<types::byte> getColumn(size_t numberColumn);
    size_t getStride();  // -- возвращает размер строки изображения в байтах
    types::Pixel_RGBA32*  getPixel(size_t x, size_t y);




private:
    ImageCommonHeader        m_header;
    std::vector<types::byte> m_data;     // -- храню все данные изображения в m_data  в формате RGBA32

};

#endif // IMAGECOMMON_H
