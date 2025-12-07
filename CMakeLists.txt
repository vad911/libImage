cmake_minimum_required(VERSION 3.19)
# -- CMakelists.txt_main  - главный
# -- Главный проект включает app и libs

set(PROJECT_NAME ProjectTestLibImage)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# -- find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

message("### --- work main Cmakelist_mainproject !!!")
# Подключаем библиотеки
add_subdirectory(libs)

# Подключаем приложение
add_subdirectory(app)




# Копируем post-commit hook, если его нет, для обновления git_info.h [1]-- 

# === Установка Git hook'ов автоматически ===
set(GIT_HOOKS_DIR "${CMAKE_SOURCE_DIR}/.git/hooks")

if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    if(WIN32)
        set(HOOK_SOURCE "${CMAKE_SOURCE_DIR}/scripts/post-commit.bat")
        set(HOOK_TARGET "${GIT_HOOKS_DIR}/post-commit.bat")
    else()
        set(HOOK_SOURCE "${CMAKE_SOURCE_DIR}/scripts/post-commit")
        set(HOOK_TARGET "${GIT_HOOKS_DIR}/post-commit")
    endif()

    if(EXISTS "${HOOK_SOURCE}" AND NOT EXISTS "${HOOK_TARGET}")
        file(COPY "${HOOK_SOURCE}" DESTINATION "${GIT_HOOKS_DIR}")
        if(NOT WIN32)
            file(CHMOD "${HOOK_TARGET}" PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE)
        endif()
        message(STATUS "Installed Git hook: ${HOOK_TARGET}")
    endif()
endif()
# Копируем post-commit hook, если его нет, для обновления git_info.h [2]-- 

