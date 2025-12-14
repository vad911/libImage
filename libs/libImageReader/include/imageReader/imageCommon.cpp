#include "imageCommon.h"

ImageCommon::ImageCommon() {}

size_t ImageCommon::getSize() {return m_data.size();}

void ImageCommon::constructNewImageCommon(const ImageCommonHeader& header,
                                          const std::vector<types::byte>& data)
{
    m_header.clear();
    m_data.clear();

    m_header = header;
    m_data   = data;
}

void ImageCommon::setHeader(const ImageCommonHeader& header)
{
    m_header = header;
}

void ImageCommon::setData(const std::vector<types::byte> &data)
{
    m_data = data;
}

std::vector<types::byte> ImageCommon::getRow(size_t numberRow)
{
    if (numberRow >= m_header.height || m_data.empty() || m_header.pixelFormat.pixelType != types::PIXELTYPE::RGBA32) {
        return {};
    }

    // Для RGBA32 каждый пиксель занимает 4 байта
    const size_t bytesPerPixel = 4;
    const size_t rowSize = m_header.width * bytesPerPixel;
    const size_t rowOffset = numberRow * rowSize;

    if (rowOffset + rowSize > m_data.size()) {
        return {};
    }

    // Копируем данные строки
    return std::vector<types::byte>(m_data.begin() + rowOffset, m_data.begin() + rowOffset + rowSize);
}

std::vector<types::byte> ImageCommon::getColumn(size_t numberColumn) {
    if (numberColumn >= m_header.width || m_data.empty() || m_header.pixelFormat.pixelType != types::PIXELTYPE::RGBA32) {
        return {};
    }

    const size_t bytesPerPixel = 4;
    const size_t rowSize = m_header.width * bytesPerPixel;     // Размер строки в байтах
    const size_t columnOffset = numberColumn * bytesPerPixel;  // Смещение колонки в строке

    std::vector<types::byte> columnData;
    columnData.reserve(m_header.height * bytesPerPixel);  // Заранее резервируем память

    // Проходим по всем строкам и собираем байты нужной колонки
    for (size_t row = 0; row < m_header.height; ++row) {
        size_t rowOffset = row * rowSize;
        size_t pixelOffset = rowOffset + columnOffset;

        if (pixelOffset + bytesPerPixel <= m_data.size()) {
            // Добавляем 4 байта пикселя (RGBA)
            columnData.insert(columnData.end(),
                              m_data.begin() + pixelOffset,
                              m_data.begin() + pixelOffset + bytesPerPixel);
        } else {
            // Если данных не хватает, добавляем нули
            columnData.insert(columnData.end(), bytesPerPixel, 0);
        }
    }

    return columnData;
}

size_t ImageCommon::getStride() {
    return m_header.width * m_header.pixelFormat.getBytesPerPixel();
}

void ImageCommonHeader::clear()
{
    pixelFormat.clear();
}
