cmake_minimum_required(VERSION 3.20)

# ----------------------
# Собираем тестовый exe  test_coreImage.cpp
# ----------------------
add_executable(test_coreImage test_coreImage.cpp)

# Подключаем библиотеку
target_link_libraries(test_coreImage PRIVATE coreImage::coreImage)

target_compile_features(test_coreImage PRIVATE cxx_std_23)




# ----------------------
# Собираем тестовый exe  test_coreImage02.cpp
# ----------------------
add_executable(test_coreImage02 test_coreImage02.cpp)


add_executable(test_coreImage03 test_coreImage03.cpp)




# Подключаем библиотеку
target_link_libraries(test_coreImage02 PRIVATE coreImage::coreImage)
target_link_libraries(test_coreImage03 PRIVATE coreImage::coreImage)

target_compile_features(test_coreImage02 PRIVATE cxx_std_23)
target_compile_features(test_coreImage03 PRIVATE cxx_std_23)