#ifndef IMAGEREADERBMP_H
#define IMAGEREADERBMP_H

#include <imageReader/types.h>
#include <imageReader/imageReaderGlobal.h>
#include <imageReader/imageReaderAbsract.h>



namespace mylibImageReader {

class CROSSPLATFORM_EXPORT_API ImageReaderBMP : public ImageReaderAbstract
{
public:
    ImageReaderBMP();

    virtual void readFile(ImageCommon&    imageCommon,  const std::string& filename)        ;
    virtual void writeFile(ImageCommon&   imageCommon,  const std::string& filename)        ;
    
    virtual void readMemory(ImageCommon&  imageCommon,  byte *pfile, size_t filesizeInBytes);
    virtual void writeMemory(ImageCommon& imageCommon,  byte *pfile, size_t filesizeInBytes);
};


}  // -- end namespace uniqueGems
#endif // IMAGEREADERBMP_H
