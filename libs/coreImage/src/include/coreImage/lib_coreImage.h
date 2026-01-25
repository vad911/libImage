#pragma once

// ============================
// Макросы экспорта для библиотеки
// ============================

#if defined(_WIN32) || defined(_WIN64)
    #ifdef COREIMAGE_EXPORTS
        // При сборке DLL
        #define COREIMAGE_API __declspec(dllexport)
    #else
        // При использовании DLL
        #define COREIMAGE_API __declspec(dllimport)
    #endif
#else
    // Для Linux/macOS shared library
    #define COREIMAGE_API __attribute__((visibility("default")))
#endif
