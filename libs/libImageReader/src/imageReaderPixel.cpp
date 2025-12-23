#include <imageReader/imageReaderPixel.h>


namespace uniqueGems {


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


} // -- end namespace uniqueGems