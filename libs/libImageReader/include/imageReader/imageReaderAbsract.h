#ifndef LIB_IMAGEREADERABSTRACT_H
#define LIB_IMAGEREADERABSTRACT_H
#pragma once

#include <imageReader/types.h>
#include <imageReader/imageCommon.h>
#include <string>


namespace uniqueGems {


using types::byte;

class ImageReaderAbstract
{




public:
    ImageReaderAbstract();
    virtual ~ImageReaderAbstract();
    virtual void readFile(ImageCommon& imageCommon,    const std::string& filename)         = 0;
    virtual void readMemory(ImageCommon& imageCommon,  byte *pfile, size_t filesizeInBytes) = 0;
    virtual void writeFile(ImageCommon& imageCommon,   const std::string& filename)         = 0;
    virtual void writeMemory(ImageCommon& imageCommon, byte *pfile, size_t filesizeInBytes) = 0;

private:

};


} // -- end namespace uniqueGems {

#endif  // -- end LIB_IMAGEREADERABSTRACT_H
