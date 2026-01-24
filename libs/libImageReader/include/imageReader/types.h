#pragma once
#ifndef LIB_IMAGEREADERTYPE_H
#define LIB_IMAGEREADERTYPE_H

#include <cstdint>
#include <imageReader/imageReaderGlobal.h>

namespace mylibImageReader {


using byte = uint8_t;


enum class ChannelSize : byte
{
    Bits1  = 1,
    Bits8  = 8,
    Bits16 = 16,
    Bits24 = 24,
    Bits32 = 32,
    Bits64 = 64
};



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


enum class FileStatus {
    EXISTS,
    NOT_EXISTS,
    IS_DIRECTORY,
    IS_SYMLINK,
    ACCESS_DENIED,
    UNKNOWN_ERROR
};



} // -- end namespace mylibImageReader




#endif  // -- end LIB_IMAGEREADERTYPE_H

