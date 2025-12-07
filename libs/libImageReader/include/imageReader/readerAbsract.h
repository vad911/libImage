#ifndef LIB_IMAGEREADERABSTRACT_H
#define LIB_IMAGEREADERABSTRACT_H
#pragma once

#include <string>


namespace uniqueGems {

class ReaderAbstract
{

using byte = unsigned char;

public:
    ReaderAbstract();
    virtual ~ReaderAbstract();
    virtual void readFile(std::string filename)                   = 0;
    virtual void readMemory(byte *pfile, size_t filesizeInBytes)  = 0;
    virtual void writeFile(std::string filename)                  = 0;
    virtual void writeMemory(byte *pfile, size_t filesizeInBytes) = 0;

private:

};


// -- end namespace uniqueGems {

#endif  // -- end LIB_IMAGEREADERABSTRACT_H