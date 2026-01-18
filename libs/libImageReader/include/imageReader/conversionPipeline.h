#pragma once
#include <imageReader/pixelConverter.h>
#include <vector>

namespace mylibImageReader
{

class ConversionPipeline
{
public:
    explicit ConversionPipeline(const ImageCommon& src);

    ConversionPipeline& to(const PixelFormat& fmt);
    bool run(ImageCommon& out);

private:
    const ImageCommon& m_src;
    std::vector<PixelFormat> m_steps;
};

ConversionPipeline convert(const ImageCommon& src);

}
