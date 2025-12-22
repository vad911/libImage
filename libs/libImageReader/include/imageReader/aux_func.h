#ifndef AUX_FUNC_H
#define AUX_FUNC_H

#include <imageReader/types.h>

#include <string>

using types::IMAGETYPES;


class Aux_Func
{
public:
    // Aux_Func();

    static std::string makeUpperString(const std::string& filename);  // -- превращает буквы в заглавные
    static std::string makeLowerString(const std::string& filename);  // -- превращает буквы в строчные

    static std::string convertImageTypes2String(const IMAGETYPES imageTypes);
    static IMAGETYPES  convertString2ImageTypes(const std::string& imageNameTypes);
    static std::string getFileExtension(const std::string& filepath);
};

#endif // AUX_FUNC_H
