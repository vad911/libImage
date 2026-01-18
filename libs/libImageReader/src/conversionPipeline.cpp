#include <imageReader/conversionPipeline.h>

namespace mylibImageReader
{

ConversionPipeline::ConversionPipeline(const ImageCommon& src)
    : m_src(src)
{
}

ConversionPipeline& ConversionPipeline::to(const PixelFormat& fmt)
{
    m_steps.push_back(fmt);
    return *this;
}

bool ConversionPipeline::run(ImageCommon& out)
{
    ImageCommon tmpA = m_src;
    ImageCommon tmpB;

    for (const auto& f : m_steps)
    {
        tmpB.width = tmpA.width;
        tmpB.height = tmpA.height;
        tmpB.format = f;
        tmpB.data.resize(tmpB.sizeBytes());

        if (!PixelConverter::convertImage(tmpA, tmpB))
            return false;

        tmpA = std::move(tmpB);
    }

    out = std::move(tmpA);
    return true;
}

ConversionPipeline convert(const ImageCommon& src)
{
    return ConversionPipeline(src);
}

}
