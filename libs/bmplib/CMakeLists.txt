cmake_minimum_required(VERSION 3.12)
project(bmplib C)

# Устанавливаем C стандарт, если нужно
set(CMAKE_C_STANDARD 99)



set(INCLUDES
    bmp-read-icons.h
    bmp-read.h
    bmp-write.h
    bmplib.h

    gen-huffman-codes.h
    huffman.h
    logging.h
    # -- test
    test-fileio-pipes.h
)



# Определяем исходные файлы библиотеки bmplib
# -- set(BMPOPEN_SRCS
set(SOURCES
    # -- bmplig.c # Возможно, здесь опечатка в названии файла в репозитории, проверьте точное имя файла .c

    bmp-read.c
    bmp-write.c
    bmp-read-loadimage.c
    bmp-read-loadindexed.c
    bmp-read-icons.c
    bmp-common.c
    huffman.c
    logging.c
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"

    # -- test
    test-fileio-pipes.c
    test-fileio-pipes.h
    test-read-conversions.c
    test-read-io.c
    test-write-helper.ods
    test-write-io.c


)


# ---------------------------------------------------- huffman-codes.h [1]
# 1. Скомпилировать вспомогательную программу-генератор
add_executable(gen-huffman gen-huffman.c)

# 2. Добавить пользовательскую команду для запуска этой программы 
#    и генерации нужного файла "huffman-codes.h"

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/huffman-codes.h"
    COMMAND $<TARGET_FILE:gen-huffman> "${CMAKE_CURRENT_BINARY_DIR}/huffman-codes.h"
    DEPENDS gen-huffman
    COMMENT "Generating huffman-codes.h using gen-huffman executable"
)

# 3. Добавить сгенерированный файл в список исходников библиотеки (это необходимо)

# Убедитесь, что эта переменная содержит все нужные .c файлы
set(SOURCES
    # ... (все ваши .c файлы, например bmplib.c, huffman.c, etc.) ...
    huffman.c 
)

# Добавляем сгенерированный файл как исходник, чтобы CMake знал, что он нужен для сборки bmplib
list(APPEND INCLUDES "${CMAKE_CURRENT_BINARY_DIR}/huffman-codes.h")

# ---------------------------------------------------- huffman-codes.h [2]







# Вставьте это в ваш CMakeLists.txt в папке bmplib

# 1. Определяем конфигурационные данные (аналог 'conf_data' в Meson)

# Определите здесь переменные, которые нужны библиотеке. 
# Например, если в config.h.in есть строка #define VERSION @VERSION@
# то вам нужно определить переменную в CMake:

set(BMPOPEN_VERSION "1.0.0") # Замените на актуальную версию

# Если нужны булевы флаги (например, поддержка какой-то функции):
set(HAVE_PTHREADS 1) # Или 0, в зависимости от того, что нужно


# Создаем саму библиотеку (можно сделать ее статической или динамической - SHARED/STATIC)
add_library(bmplib SHARED 
# -- ${BMPOPEN_SRCS}
     ${INCLUDES}
     ${SOURCES}
     
)




# 2. Вызываем configure_file для обработки шаблона config.h.in

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"  # Исходный файл шаблона
    "${CMAKE_CURRENT_BINARY_DIR}/config.h"    # Куда сохранить сгенерированный файл
    @ONLY                                     # Важно: обрабатывает только синтаксис @VAR@
)

# 3. Убедитесь, что компилятор видит сгенерированный config.h

# Сгенерированный файл находится в папке сборки (CMAKE_CURRENT_BINARY_DIR).
# Нужно добавить эту папку в пути поиска заголовочных файлов для библиотеки:

target_include_directories(bmplib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_BINARY_DIR}" # Добавляем путь к сгенерированному config.h
)


# Указываем, где искать заголовочные файлы
target_include_directories(bmplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Добавляем правила установки
install(TARGETS bmplib DESTINATION lib)
install(FILES bmplib.h DESTINATION include)