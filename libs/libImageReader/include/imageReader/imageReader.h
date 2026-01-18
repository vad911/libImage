#ifndef LIB_IMAGEREADER_H
#define LIB_IMAGEREADER_H
#pragma once

#include <string>
#include <imageReader/imageReaderAbsract.h>


// -- TODO подбор названия 
// -- uniqueGems
// -- Это составное слово из двух латинских корней:
// -- Sol (сущ., муж. р.) — солнце.
// -- Ascindit (глагол, 3 лицо, ед. число) — от ascindo, ascindere, ascidi, ascissum. Его основное значение: рассекать, разрезать, разрывать, раздирать.
// -- Буквальный перевод: «Солнце рассекает / разрывает (что-то)».
// namespace SolAscindit
// namespace uniqueGems

namespace mylibImageReader {

class CROSSPLATFORM_EXPORT_API ImageReader  : public ImageReaderAbstract
{
public:
    virtual void readFile(ImageCommon& imageCommon,    const std::string& filename);
    virtual void readMemory(ImageCommon& imageCommon,  byte *pfile, size_t filesizeInBytes);
    virtual void writeFile(ImageCommon& imageCommon,   const std::string& filename);
    virtual void writeMemory(ImageCommon& imageCommon, byte *pfile, size_t filesizeInBytes);
private:

};

} // -- end uniqueGems

#endif  // -- end LIB_IMAGEREADER_H
