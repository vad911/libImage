#ifndef IMAGEREADERFABRIC_H
#define IMAGEREADERFABRIC_H

#include <imageReader/types.h>
#include <imageReader/imageReaderAbsract.h>
#include <memory>



namespace uniqueGems {

class ImageReaderFabric
{
public:
    ImageReaderFabric();
    std::unique_ptr<ImageReaderAbstract> createReader(const std::string &fullpath);
};

}  // -- end namespace uniqueGems

#endif // IMAGEREADERFABRIC_H
