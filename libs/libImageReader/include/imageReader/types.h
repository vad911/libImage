#ifndef LIB_IMAGEREADERTYPE_H
#define LIB_IMAGEREADERTYPE_H
#pragma once

#include <cstddef>
#include <imageReader/imageReaderGlobal.h>

namespace types {

using byte = unsigned char;

enum class IMAGETYPES: int
{
    NoType,
    PNG,
    BMP,
    GIF,
    JPG,
    JPEG,
    JPEGXR,
    WEBP,
};





enum class PIXELTYPE : int {
    NotDefine,
    BW1,          // -- black white pixel size = 1 bit   0 or 1
    BW8,          // -- black white pixel size = 8 bit   00000000 or 00000001 [0...1 in byte]
    GRAY8,        // -- gray  pixel size = 8 bit  [0...256]
    GRAYALPHA16,  // -- gray  pixel size = 8 bit  [0...256]
    RGB556,       // -- pixel size = 16 bit,  red 5 bit, green - 5 bit, blue - 6 bit
    RGB24,        // -- pixel size = 24 bit:  red -8bit, green - 8 bit, blue - 8 bit
    RGBA32,       // -- pixel size = 32 bit:  red -8bit, green - 8 bit, blue - 8 bit, alpha - 8 bit
    BGR24,        // -- pixel size = 24 bit:  red -8bit, green - 8 bit, blue - 8 bit
    BGRA32,       // -- pixel size = 32 bit:  red -8bit, green - 8 bit, blue - 8 bit, alpha - 8 bit
};


struct CROSSPLATFORM_EXPORT_API PixelFormat {
    PIXELTYPE pixelType;
    void clear();

    int getBytesPerPixel();
    // -- return in bytes
    size_t getPixelSizeInBytes (const PIXELTYPE pixelType);
    // -- return in bytes
    size_t getPixelSizeInBites (const PIXELTYPE pixelType);
};



} // -- end namespace types

#endif  // -- end LIB_IMAGEREADERTYPE_H

