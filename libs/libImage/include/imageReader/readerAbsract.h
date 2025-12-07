#ifndef LIB_IMAGEREADERABSTRACT_H
#define LIB_IMAGEREADERABSTRACT_H
#pragma once

#include <string>

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

#endif  // -- end LIB_IMAGEREADERABSTRACT_H