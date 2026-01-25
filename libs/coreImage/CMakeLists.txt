cmake_minimum_required(VERSION 3.20)

# ─────────────────────────────────────────────
# Project
# ─────────────────────────────────────────────
project(
    coreImage
    VERSION 0.1.0
    DESCRIPTION "Core image processing library"
    LANGUAGES CXX
)

# ─────────────────────────────────────────────
# Options
# ─────────────────────────────────────────────
option(COREIMAGE_BUILD_SHARED "Build coreImage as shared library" ON)
option(COREIMAGE_BUILD_TESTS  "Build tests" OFF)

# ─────────────────────────────────────────────
# C++ standard
# ─────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ─────────────────────────────────────────────
# Library type
# ─────────────────────────────────────────────
if (COREIMAGE_BUILD_SHARED)
    set(COREIMAGE_LIB_TYPE SHARED)
else()
    set(COREIMAGE_LIB_TYPE STATIC)
endif()

# ─────────────────────────────────────────────
# Paths
# ─────────────────────────────────────────────
set(COREIMAGE_SRC_DIR     ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(COREIMAGE_INCLUDE_DIR ${COREIMAGE_SRC_DIR}/include)

# ─────────────────────────────────────────────
# Sources
# ─────────────────────────────────────────────
set(COREIMAGE_HEADERS
    ${COREIMAGE_INCLUDE_DIR}/coreImage/types.h
    ${COREIMAGE_INCLUDE_DIR}/coreImage/channel.h

    ${COREIMAGE_INCLUDE_DIR}/coreImage/channel_info.h
    ${COREIMAGE_INCLUDE_DIR}/coreImage/channel_data.h
)

set(COREIMAGE_SOURCES
    ${COREIMAGE_SRC_DIR}/types.cpp
    ${COREIMAGE_SRC_DIR}/channel.cpp
    ${COREIMAGE_SRC_DIR}/channel_info.cpp
    ${COREIMAGE_SRC_DIR}/channel_data.cpp
)

# ─────────────────────────────────────────────
# Target
# ─────────────────────────────────────────────
add_library(coreImage
    ${COREIMAGE_LIB_TYPE}
    ${COREIMAGE_HEADERS}
    ${COREIMAGE_SOURCES}
)

add_library(coreImage::coreImage ALIAS coreImage)

# ─────────────────────────────────────────────
# Include directories
# ─────────────────────────────────────────────
target_include_directories(coreImage
    PUBLIC
        $<BUILD_INTERFACE:${COREIMAGE_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# ─────────────────────────────────────────────
# Compile features & warnings
# ─────────────────────────────────────────────
target_compile_features(coreImage PUBLIC cxx_std_23)

if (MSVC)
    target_compile_options(coreImage PRIVATE /W4 /permissive-)
else()
    target_compile_options(coreImage PRIVATE -Wall -Wextra -Wpedantic)
endif()

# ─────────────────────────────────────────────
# Properties
# ─────────────────────────────────────────────
include(GNUInstallDirs)

set_target_properties(coreImage PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

# ─────────────────────────────────────────────
# Install
# ─────────────────────────────────────────────
install(
    TARGETS coreImage
    EXPORT coreImageTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(
    DIRECTORY ${COREIMAGE_INCLUDE_DIR}/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ─────────────────────────────────────────────
# Export package
# ─────────────────────────────────────────────
install(
    EXPORT coreImageTargets
    FILE coreImageTargets.cmake
    NAMESPACE coreImage::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/coreImage
)

# ─────────────────────────────────────────────
# Tests (future)
# ─────────────────────────────────────────────
if (COREIMAGE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
