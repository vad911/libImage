#include <imageReader/uploadContext.h>
#include <GL/gl.h>
#include <cassert>

namespace mylibImageReader
{

UploadContext::UploadContext() = default;

UploadContext::~UploadContext()
{
    destroyPBOs();
}

void UploadContext::init(int w, int h, const PixelFormat& fmt)
{
    if (w == m_width && h == m_height && fmt == m_fmt)
        return;

    destroyPBOs();

    m_width  = w;
    m_height = h;
    m_fmt    = fmt;

    m_sizeBytes = fmt.pixelSizeBytes() * w * h;

    createPBOs();
}

void UploadContext::createPBOs()
{
    glGenBuffers(2, m_pbos);

    for (int i = 0; i < 2; ++i)
    {
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbos[i]);
        glBufferData(
            GL_PIXEL_UNPACK_BUFFER,
            m_sizeBytes,
            nullptr,
            GL_STREAM_DRAW
        );
    }
}

void UploadContext::destroyPBOs()
{
    if (m_pbos[0])
        glDeleteBuffers(2, m_pbos);

    m_pbos[0] = m_pbos[1] = 0;
}

uint8_t* UploadContext::map()
{
    m_index = (m_index + 1) & 1;

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, m_pbos[m_index]);

    return static_cast<uint8_t*>(
        glMapBufferRange(
            GL_PIXEL_UNPACK_BUFFER,
            0,
            m_sizeBytes,
            GL_MAP_WRITE_BIT |
            GL_MAP_INVALIDATE_BUFFER_BIT |
            GL_MAP_UNSYNCHRONIZED_BIT
        )
    );
}

void UploadContext::unmapAndUpload(unsigned tex)
{
    glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

    glBindTexture(GL_TEXTURE_2D, tex);

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0,
        0, 0,
        m_width,
        m_height,
        m_fmt.glFormat(),   // GL_RGBA / GL_BGRA
        m_fmt.glType(),     // GL_UNSIGNED_BYTE
        nullptr             // from PBO
    );

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

} // namespace
