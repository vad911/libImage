#pragma once

#include <iostream>
#include <array>


// using  byte  = unsigned char;
using  byte  = uint8_t;

enum class biCompressionType : int {
    notDefine = -1,
    BI_RGB    =  0,    // -- Без сжатия - наиболее распространенный формат
    BI_RLE8,           // -- RLE-сжатие для 8-битных изображений
    BI_RLE4,           // -- RLE-сжатие для 4-битных изображений
    BI_BITFIELDS,      // -- Без сжатия с цветовыми масками (для 16 и 32 бит)
    BI_JPEG,           // -- Встроенное JPEG изображение (только для принтеров)
    BI_PNG,            // -- Встроенное PNG изображение (только для принтеров)
    BI_ALPHABITFIELDS, // -- С масками цвета + альфа-канал (RGBA)
    BI_CMYK,           // -- Без сжатия CMYK
    BI_CMYKRLE8,       // -- RLE-сжатие CMYK (8 бит)
    BI_CMYKRLE4,       // -- RLE-сжатие CMYK (4 бит)
};


struct __attribute__((packed)) BmpFileHeader  // -- size 14 bytes
{
    // -- char magicWord[2];  // -- magic word "BM"
    std::array<char, 2> m_bfType = {'B', 'M'};   // -- magic word "BM"
    int                 m_bfSize;                // -- Размер всего файла в байтах
    byte                m_reserved_01[2];        // -- Зарезервировано 1
    byte                m_reserved_02[2];        // -- Зарезервировано 2
    int                 m_bfOffBits;             // -- Смещение до начала пиксельных данных от начала файла
};


struct __attribute__((packed)) BmpBitmapInfoHeader  // -- size 40 bytes 
{
    int                 m_biSize;          // -- Размер этого заголовка (40 байт)
    int                 m_biWidth;         // -- Ширина изображения в пикселях (может быть отрицательной)
    int                 m_biHeight;        // -- Высота: >0 – данные снизу вверх, <0 – сверху вниз
    short               m_biPlanes;        // -- Число плоскостей (всегда 1)
    short               m_biBitCount;      // -- Бит на пиксель (1, 4, 8, 16, 24, 32)
    biCompressionType   m_biCompression;   // -- Тип сжатия (0 = BI_RGB, 1 = BI_RLE8, 2 = BI_RLE4, 3 = BI_BITFIELDS
    int                 m_biSizeImage;     // -- Размер пиксельных данных (0 если несжатое BI_RGB)
    int                 m_biXPelsPerMeter; // -- Горизонтальное разрешение (пикселей/метр)
    int                 m_biYPelsPerMeter; // -- Вертикальное разрешение (пикселей/метр)
    int                 m_biClrUsed;       // -- Число используемых цветов в палитре (0 = все)
    int                 m_biClrImportant;  // -- Число важных цветов (0 = все важны)
};



struct Pixel {
    
};

struct Pixel_BGRA : Pixel
{
    byte Blue;
    byte Green;
    byte Red;
    byte Reserved;
};