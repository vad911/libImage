#pragma once
#ifndef LIB_IMAGEREADERTYPE_H
#define LIB_IMAGEREADERTYPE_H

#include <cstdint>
#include <imageReader/imageReaderGlobal.h>

namespace mylibImageReader {

using byte = uint8_t;


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

