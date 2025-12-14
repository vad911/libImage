#ifndef LIB_IMAGEREADERTYPE_H
#define LIB_IMAGEREADERTYPE_H
#pragma once

#include <cstddef>

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


struct PixelFormat {
    PIXELTYPE pixelType;
    void clear();

    int getBytesPerPixel();
    // -- return in bytes
    size_t getPixelSizeInBytes (const PIXELTYPE pixelType);
    // -- return in bytes
    size_t getPixelSizeInBites (const PIXELTYPE pixelType);
};

struct Pixel_Abstract {
    virtual ~Pixel_Abstract();
    PixelFormat pixelFormat;
    size_t getPixelSize();
    virtual byte* getData() = 0;
};


struct Pixel_BW1 : public Pixel_Abstract
{
    byte data[1];
    byte* getData();

};

struct Pixel_BW8 : public Pixel_Abstract
{
    byte data[1];
    byte* getData();
};


struct Pixel_Gray8 : public Pixel_Abstract
{
    byte data[1];
    byte* getData();
};

struct Pixel_GrayAlpha16 : public Pixel_Abstract
{
    byte data[2];
    byte* getData();
};

struct Pixel_RGB556  : public Pixel_Abstract
{
    byte data[2];
    byte* getData();
};

struct Pixel_RGB24 : public Pixel_Abstract
{
    byte data[3];
    byte* getData();
};

struct Pixel_BGR24 : public Pixel_Abstract
{
    byte data[3];
    byte* getData();
};

struct Pixel_BGRA32 : public Pixel_Abstract
{
    byte data[4];
    byte* getData();
};

struct Pixel_RGBA32 : public Pixel_Abstract
{
    byte data[4];
    byte* getData();
};




} // -- end namespace types

#endif  // -- end LIB_IMAGEREADERTYPE_H
