#pragma once
#include <imageReader/pixelFormat.h>
#include <string>

namespace mylibImageReader
{

struct PixelFormatValidationResult
{
    bool valid = true;
    std::string error;
};

class PixelFormatValidator
{
public:
    static PixelFormatValidationResult validate(const PixelFormat& fmt);
};

}
