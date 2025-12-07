cmake_minimum_required(VERSION 3.19)
# -- CMakelists.txt_main  - главный
# -- Главный проект включает app и libs
set(PROJECT_NAME ProjectSandBox)

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

# -- find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Подключаем библиотеки
add_subdirectory(libs)

# Подключаем приложение
add_subdirectory(app)
