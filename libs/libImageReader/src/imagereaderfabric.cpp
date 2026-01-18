#include <imageReader/imagereaderfabric.h>
#include <imageReader/aux_func.h>

#include <imageReader/imageReader_BMP.h>

namespace mylibImageReader {


ImageReaderFabric::ImageReaderFabric()
{
}

std::unique_ptr<ImageReaderAbstract> ImageReaderFabric::createReader(const std::string &fullpath)
{
    // -- форматирование расширения
    std::string extension = Aux_Func::getFileExtension(fullpath);
    std::string ext       = Aux_Func::makeLowerString(extension);
    IMAGETYPES imageType  = Aux_Func::convertString2ImageTypes(ext);

    switch(imageType){
        case IMAGETYPES::BMP: { return  std::make_unique<ImageReaderBMP>();  break;}
        default: {throw std::runtime_error("Unsupported image format: " + ext);}

    }

    throw std::runtime_error("Unsupported image format: " + ext);
}


} //  -- end namespace uniqueGems {
