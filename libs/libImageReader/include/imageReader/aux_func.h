#ifndef AUX_FUNC_H
#define AUX_FUNC_H

#include <imageReader/types.h>

#include <filesystem>
#include <string>
#include <iostream>

using types::IMAGETYPES;
using types::FileStatus;

class Aux_Func
{
public:
    // Aux_Func();
    bool fileExists(const std::string& filePath); // -- проверка файла на существование
    FileStatus checkFile(const std::string& filePath);

    static std::string makeUpperString(const std::string& filename);  // -- превращает буквы в заглавные
    static std::string makeLowerString(const std::string& filename);  // -- превращает буквы в строчные

    static std::string convertImageTypes2String(const IMAGETYPES imageTypes);
    static IMAGETYPES  convertString2ImageTypes(const std::string& imageNameTypes);
    static std::string getFileExtension(const std::string& filepath);
};

#endif // AUX_FUNC_H
