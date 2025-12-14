cmake_minimum_required(VERSION 3.19)

set(LIB_IMAGEREADER imageReader)

set(PROJECT_NAME ${LIB_IMAGEREADER})

project(${PROJECT_NAME} LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Подключаем отдельный CMake-файл, который создаст git_info.h
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/findGitCommit.cmake)

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTS "Build tests" OFF)

# -------------------- определени комита get git info for make version [1]-- 
# Вызываем функцию для получения Git информации
find_git_commit()

# Устанавливаем дату сборки
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")

# Создаем header файл с информацией о версии
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/imageReader/versionInfo.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/imageReader/versionInfo.h
    @ONLY
)

# Создаем каталог для сгенерированных заголовочных файлов
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/imageReader)
# -------------------- определени комита get git info for make version [2]-- 

set(INCLUDES
    include/imageReader/imageReader.h
    ${CMAKE_CURRENT_BINARY_DIR}/include/imageReader/versionInfo.h
    include/imageReader/versionInfo.h.in
    include/imageReader/git_info.h.in
    include/imageReader/types.h
)

set(SOURCE
    src/imageReader.cpp
    src/versionInfo.cpp
)

# Добавляем библиотеку
add_library(${LIB_IMAGEREADER}
    ${SOURCE}
    ${INCLUDES}
    src/types.cpp
    include/imageReader/imageCommon.h include/imageReader/imageCommon.cpp
)

message (" ###### --- where include :   ${CMAKE_CURRENT_BINARY_DIR}/include/imageReader/versionInfo.h")
message (" ###### --- target  where include :   ${CMAKE_CURRENT_SOURCE_DIR}/include/versionInfo.h")

# Публичные заголовки (добавляем сгенерированную директорию)
target_include_directories(${LIB_IMAGEREADER} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Компиляционные флаги
target_compile_options(${LIB_IMAGEREADER} PRIVATE -Wall -Wextra -Werror)
