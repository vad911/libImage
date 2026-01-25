cmake_minimum_required(VERSION 3.20)

# ----------------------
# Собираем тестовый exe
# ----------------------
add_executable(test_coreImage test_coreImage.cpp)

# Подключаем библиотеку
target_link_libraries(test_coreImage PRIVATE coreImage::coreImage)

target_compile_features(test_coreImage PRIVATE cxx_std_23)
