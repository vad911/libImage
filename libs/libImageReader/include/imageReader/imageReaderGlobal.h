#pragma once

// -- Проверка компилятора
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__)
    #define OS_WINDOWS
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    #define OS_LINUX
#else
    #error "Unsupported platform"
#endif

// -- Макросы для экспорта/импорта
#ifdef BUILD_SHARED_LIB
    #ifdef OS_WINDOWS
        #define LIB_EXPORT __declspec(dllexport)
        #define LIB_IMPORT __declspec(dllimport)
    #else
        #define LIB_EXPORT __attribute__((visibility("default")))
        #define LIB_IMPORT
    #endif
#else
    #ifdef OS_WINDOWS
        #define LIB_EXPORT
        #define LIB_IMPORT __declspec(dllimport)
    #else
        #define LIB_EXPORT
        #define LIB_IMPORT
    #endif
#endif

// -- Универсальный макрос для использования в коде
#ifdef CROSSPLATFORM_LIB_EXPORTS
    #define CROSSPLATFORM_EXPORT_API LIB_EXPORT
#else
    #define CROSSPLATFORM_EXPORT_API LIB_IMPORT
#endif

// -- Для C функций (без mangling имен)
#ifdef __cplusplus
    #define EXTERN_C extern "C"
#else
    #define EXTERN_C
#endif

#define C_API EXTERN_C CROSSPLATFORM_EXPORT_API