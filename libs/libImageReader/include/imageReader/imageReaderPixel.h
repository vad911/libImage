#pragma once
#include <imageReader/types.h>



namespace uniqueGems {

    using types::PixelFormat;
    using types::byte;
    using types::IMAGETYPES;

struct CROSSPLATFORM_EXPORT_API Pixel_Abstract {
    virtual ~Pixel_Abstract();
    PixelFormat pixelFormat;
    size_t getPixelSize();
    virtual byte* getData() = 0;
};


struct CROSSPLATFORM_EXPORT_API Pixel_BW1 : public Pixel_Abstract
{
    byte data[1];
    byte* getData();

};

struct CROSSPLATFORM_EXPORT_API Pixel_BW8 : public Pixel_Abstract
{
    byte data[1];
    byte* getData();
};


struct CROSSPLATFORM_EXPORT_API Pixel_Gray8 : public Pixel_Abstract
{
    byte data[1];
    byte* getData();
};

struct CROSSPLATFORM_EXPORT_API Pixel_GrayAlpha16 : public Pixel_Abstract
{
    byte data[2];
    byte* getData();
};

struct CROSSPLATFORM_EXPORT_API  Pixel_RGB556 : public Pixel_Abstract
{
    byte data[2];
    byte* getData();
};

struct CROSSPLATFORM_EXPORT_API Pixel_RGB24 : public Pixel_Abstract
{
    byte data[3];
    byte* getData();
};

struct CROSSPLATFORM_EXPORT_API Pixel_BGR24 : public Pixel_Abstract
{
    byte data[3];
    byte* getData();
};

struct CROSSPLATFORM_EXPORT_API Pixel_BGRA32 : public Pixel_Abstract
{
    byte data[4];
    byte* getData();
};

struct CROSSPLATFORM_EXPORT_API Pixel_RGBA32 : public Pixel_Abstract
{
    byte data[4];
    byte* getData();
};




} // -- 