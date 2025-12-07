cmake_minimum_required(VERSION 3.19)


# -- CMakelists.txt_app  - отвечает только за сборку всех нижележащих библиотек
# -- указывает какие libs собрать
set(PROJECT_NAME LibsBundle)

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

message("### --- work libBandle Cmakelist_libBandle !!!")

# -- find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# Подключаем библиотеки
add_subdirectory(libImageReader)
# add_subdirectory(libeigen)
# add_subdirectory(libqwt)
