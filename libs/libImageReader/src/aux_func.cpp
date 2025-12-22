#include <imageReader/aux_func.h>

// Aux_Func::Aux_Func() {}



std::string Aux_Func::makeUpperString(const std::string& filename) {
    std::string result = filename;  // Создаем копию исходной строки

    // Преобразуем каждый символ в верхний регистр
    for (char& c : result) {
        c = std::toupper(static_cast<unsigned char>(c));
    }

    return result;
}


std::string Aux_Func::makeLowerString(const std::string& filename) {
    std::string result = filename;  // Создаем копию исходной строки

    // Преобразуем каждый символ в нижний регистр
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }

    return result;
}


std::string Aux_Func::convertImageTypes2String(const IMAGETYPES imageTypes)
{
    std::string nameType = "";
    switch (imageTypes)
    {
    case IMAGETYPES::BMP:    {nameType = "bmp";    break;}
    case IMAGETYPES::JPG:    {nameType = "jpg";    break;}
    case IMAGETYPES::PNG:    {nameType = "png";    break;}
    case IMAGETYPES::GIF:    {nameType = "gif";    break;}
    case IMAGETYPES::JPEGXR: {nameType = "jpgxr";  break;}
    case IMAGETYPES::WEBP:   {nameType = "webp";   break;}
    default:                 {nameType = "NoType"; break;}
    }

    return nameType;
}

IMAGETYPES Aux_Func::convertString2ImageTypes(const std::string &imageNameTypes_AnyCase)
{
    std::string imageNameTypes = makeLowerString(imageNameTypes_AnyCase);

    IMAGETYPES imageTypes = IMAGETYPES::NoType;
    if (imageNameTypes == "bmp")
    {
        imageTypes = IMAGETYPES::BMP;
    }

    if (imageNameTypes == "jpg" ||  imageNameTypes == "jpeg")
    {
        imageTypes = IMAGETYPES::JPG;
    }

    if (imageNameTypes == "png")
    {
        imageTypes = IMAGETYPES::PNG;
    }

    if (imageNameTypes == "webp")
    {
        imageTypes = IMAGETYPES::WEBP;
    }

    if (imageNameTypes == "jpegxr" || imageNameTypes == "jpgxr")
    {
        imageTypes = IMAGETYPES::JPEGXR;
    }

    return imageTypes;
}

std::string Aux_Func::getFileExtension(const std::string &filepath)
{
    if (filepath.empty()) {
        return "";
    }

    // Находим последнюю точку
    size_t dotPos = filepath.find_last_of('.');

    // Если точка не найдена или является последним символом
    if (dotPos == std::string::npos || dotPos == filepath.length() - 1) {
        return "";
    }

    // Находим последний разделитель пути
    size_t slashPos = filepath.find_last_of("/\\");

    // Проверяем, что точка находится после последнего разделителя
    if (slashPos != std::string::npos && dotPos < slashPos) {
        return "";
    }

    // Извлекаем расширение
    std::string extension = filepath.substr(dotPos + 1);

    // Опционально: преобразуем в нижний регистр для единообразия
    std::transform(extension.begin(), extension.end(), extension.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    return extension;
}
