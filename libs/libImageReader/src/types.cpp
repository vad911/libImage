#include <imageReader/types.h>


namespace types {

void PixelFormat::clear()
{
    pixelType = PIXELTYPE::NotDefine;
}

int PixelFormat::getBytesPerPixel() {
    return getPixelSizeInBytes(pixelType);
}

size_t PixelFormat::getPixelSizeInBytes(const PIXELTYPE pixelType) {
    size_t result = 0;
    switch (pixelType)
    {
    case PIXELTYPE::BW1:         {result = 1;  break;}
    case PIXELTYPE::BW8:         {result = 1;  break;}
    case PIXELTYPE::GRAY8:       {result = 1;  break;}
    case PIXELTYPE::GRAYALPHA16: {result = 2;  break;}
    case PIXELTYPE::RGB556:      {result = 2;  break;}
    case PIXELTYPE::RGB24:       {result = 3;  break;}
    case PIXELTYPE::RGBA32:      {result = 4;  break;}
    case PIXELTYPE::BGR24:       {result = 3;  break;}
    case PIXELTYPE::BGRA32:      {result = 4;  break;}
    default: {result = 0;  break;}
    }
    return result;
}

size_t PixelFormat::getPixelSizeInBites(const PIXELTYPE pixelType) {
    size_t result = 0;
    switch (pixelType)
    {
    case PIXELTYPE::BW1:         {result =  1;  break;}
    case PIXELTYPE::BW8:         {result =  8;  break;}
    case PIXELTYPE::GRAY8:       {result =  8;  break;}
    case PIXELTYPE::GRAYALPHA16: {result = 16;  break;}
    case PIXELTYPE::RGB556:      {result = 16;  break;}
    case PIXELTYPE::RGB24:       {result = 24;  break;}
    case PIXELTYPE::RGBA32:      {result = 32;  break;}
    case PIXELTYPE::BGR24:       {result = 24;  break;}
    case PIXELTYPE::BGRA32:      {result = 32;  break;}
    default: {result = 0;  break;}
    }
    return result;
}


size_t Pixel_Abstract::getPixelSize() {
    return pixelFormat.getBytesPerPixel();
}

byte *Pixel_BW1::getData() {return data;}

byte *Pixel_BW8::getData() {return data;}

byte *Pixel_Gray8::getData() {return data;}

byte *Pixel_GrayAlpha16::getData() {return data;}

byte *Pixel_RGB556::getData() {return data;}

byte *Pixel_RGB24::getData() {return data;}

byte *Pixel_BGR24::getData() {return data;}

byte *Pixel_BGRA32::getData() {return data;}

byte *Pixel_RGBA32::getData() {return data;}




} // -- end namespace types
