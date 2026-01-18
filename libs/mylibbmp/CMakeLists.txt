cmake_minimum_required(VERSION 3.19)

set(LIB_BMP mylibbmp)

set(PROJECT_NAME ${LIB_BMP})

project(${PROJECT_NAME} LANGUAGES CXX)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTS "Build tests" OFF)



set(INCLUDES
    include/mylibbmp/types.h
    include/mylibbmp/BmpImage.h
    
)

set(SOURCE
    # -- src/imageReader.cpp
    src/BmpImage.cpp
)

# Добавляем библиотеку
add_library(${LIB_BMP}
    ${SOURCE}
    ${INCLUDES}
)



# Публичные заголовки (добавляем сгенерированную директорию)
target_include_directories(${LIB_BMP} PUBLIC 
    # -- $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)



# -- target_link_libraries(${LIB_BMP}
# --     PRIVATE bmplib
# -- )


# Компиляционные флаги
target_compile_options(${LIB_BMP} PRIVATE -Wall -Wextra -Werror)
