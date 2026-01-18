#include <imageReader/imageReader_BMP.h>
#include <bmplib.h>
//-- #include <bmpfile.h>

namespace mylibImageReader {

ImageReaderBMP::ImageReaderBMP() {}

using mylibImageReader::byte;

void ImageReaderBMP::readFile([[maybe_unused]] ImageCommon &imageCommon, [[maybe_unused]] const std::string &filename)
{
   
}

void ImageReaderBMP::readMemory([[maybe_unused]] ImageCommon &imageCommon, [[maybe_unused]] byte *pfile, [[maybe_unused]] size_t filesizeInBytes)
{

}

void ImageReaderBMP::writeFile([[maybe_unused]] ImageCommon &imageCommon, [[maybe_unused]] const std::string &filename)
{
   
}

void ImageReaderBMP::writeMemory([[maybe_unused]] ImageCommon &imageCommon, [[maybe_unused]] byte *pfile, [[maybe_unused]] size_t filesizeInBytes)
{

}


} // -- end namespace uniqueGems
