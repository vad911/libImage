cmake_minimum_required(VERSION 3.19)

# -- CMakelists.txt_app  - отвечает только за приложение
# -- включает команды только для app

set(PROJECT_NAME Qt_SandBox005)
project( ${PROJECT_NAME} LANGUAGES CXX)


# -------------------- определени комита get git info for make version [1]-- 
# Включаем наш модуль
include(cmake/findGitCommit.cmake)

# Вызываем функцию для получения Git информации
find_git_commit()

# Устанавливаем дату сборки
string(TIMESTAMP BUILD_DATE "%Y-%m-%d %H:%M:%S")

# Создаем header файл с информацией о версии
configure_file(
    ${CMAKE_SOURCE_DIR}/include/app/version.h.in
    ${CMAKE_BINARY_DIR}/include/app/version.h
)
# -------------------- определени комита get git info for make version [2]-- 


find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)



# -- Установка C++20 перед вызовом qt_standard_project_setup
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup()


set(APP_INCLUDES
 # -- app/include/app/mainwindow.h
    app/include/app/versionInfo.h
)

set(APP_SOURCES
    src/main.cpp
    src/versionInfo.cpp
)

set(APP_UI
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui

    ui/aboutDialog.h
    ui/aboutDialog.cpp
    ui/aboutDialog.ui
)

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    ${APP_INCLUDES}
    ${APP_SOURCES}
    ${APP_UI}

)

qt_add_translations(
    TARGETS ${PROJECT_NAME}
    TS_FILES src/Qt_SandBox005_ru_RU.ts
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt::Core
        Qt::Widgets
)


# Указываем include директории
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ui           # для mainwindow.h
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

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
