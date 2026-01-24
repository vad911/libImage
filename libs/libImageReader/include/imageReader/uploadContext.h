#pragma once

#include <imageReader/pixelFormat.h>

namespace mylibImageReader
{

class UploadContext
{
public:
    UploadContext();
    ~UploadContext();

    void init(int width, int height, const PixelFormat& fmt);

    // CPU writes here
    uint8_t* map();

    // GPU reads here
    void unmapAndUpload(unsigned textureId);

    int width()  const;
    int height() const;
    const PixelFormat& format() const;

private:
    void createPBOs();
    void destroyPBOs();

    unsigned m_pbos[2]{0, 0};
    int      m_index = 0;

    int         m_width  = 0;
    int         m_height = 0;
    PixelFormat m_fmt;

    size_t m_sizeBytes = 0;
};

} // namespace
