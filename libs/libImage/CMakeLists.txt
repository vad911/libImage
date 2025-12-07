cmake_minimum_required(VERSION 3.19)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции сборки
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_TESTS "Build tests" OFF)

set (${LIB_IMAGEREADER} imageReader)

set(PROJECT_NAME ${LIB_IMAGEREADER})

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)


set(INCLUDES
    include/imageReader/imageReader.h
)


set(SOURCE
    src/imageReader.cpp
)


# Добавляем библиотеку
add_library(${LIB_IMAGEREADER}
    ${SOURCE}
    ${INCLUDES}
)


# Публичные заголовки
target_include_directories(${LIB_IMAGEREADER} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Компиляционные флаги
target_compile_features(${LIB_IMAGEREADER} PUBLIC cxx_std_20)
target_compile_options(${LIB_IMAGEREADER}  PRIVATE -Wall -Wextra -Werror)

# -- find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Подключаем библиотеки
# add_subdirectory(libeigen)
# add_subdirectory(libqwt)
