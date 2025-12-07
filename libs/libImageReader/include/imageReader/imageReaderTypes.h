#ifndef LIB_IMAGEREADERTYPES_H
#define LIB_IMAGEREADERTYPES_H
#pragma once

#include <string>

namespace uniqueGems {

class ReaderAbstract
{
public:
    ReaderAbstract();
    virtual ~ReaderAbstract();
    virtual void readFile(std::string filename)            = 0;
    virtual void readMemory(void *pfile, size_t filesize)  = 0;
    virtual void writeFile(std::string filename)           = 0;
    virtual void writeMemory(void *pfile, size_t filesize) = 0;

private:
    
};

// --end namespace uniqueGems 

#endif  // -- end LIB_IMAGEREADERTYPES_H