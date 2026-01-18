#pragma once

#include <mylibbmp/types.h>
#include <vector>

using ColorTable = std::vector<byte>;
// using ColorTable = std::vector<Pixel>;
using DataRow   = std::vector<byte>;   // -- строчка с данными
using DataImage = std::vector<DataRow>;

class BmpImage {

public:
    BmpFileHeader        m_fileHeader;  // -- 14 байт 
    BmpBitmapInfoHeader  m_infoHeader;  // -- 40 байт
    ColorTable           m_colorTable;  // -- может отсуствовать
    DataImage            m_dataImage;   // -- сами данные картинки

};