cmake_minimum_required(VERSION 3.19)

# -- CMakelists.txt_app  - отвечает только за приложение
# -- включает команды только для app

message("### --- work app Cmakelist_app !!!")
set(PROJECT_NAME AppTestLibImage)
project( ${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)



# -- find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)



# -- Установка C++20 перед вызовом qt_standard_project_setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -- qt_standard_project_setup()


set(APP_INCLUDES

    # app/include/app/versionInfo.h
)

set(APP_SOURCES
    src/main.cpp
    # src/versionInfo.cpp
)


add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    ${APP_INCLUDES}
    ${APP_SOURCES}
)



target_link_libraries(${PROJECT_NAME}
    PRIVATE imageReader
)


# Указываем include директории
target_include_directories(${PROJECT_NAME} PRIVATE
    # -- ${CMAKE_CURRENT_SOURCE_DIR}/ui           # для mainwindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/app      # для functions.h
    # -- ${CMAKE_CURRENT_SOURCE_DIR}/src          # для текущей директории с исходниками
)

# --- install --
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
