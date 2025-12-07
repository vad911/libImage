# findGitCommit.cmake
function(find_git_commit)
    find_package(Git QUIET)
    
    if(NOT GIT_FOUND)
        message(WARNING "Git not found - cannot determine commit information")
        set(GIT_COMMIT_HASH "unknown" PARENT_SCOPE)
        set(GIT_BRANCH "unknown" PARENT_SCOPE)
        set(GIT_COMMIT_DATE "unknown" PARENT_SCOPE)
        set(GIT_TAG "unknown" PARENT_SCOPE)
        return()
    endif()
    
    # Получаем хэш коммита
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    # Получаем текущую ветку
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    # Получаем дату последнего коммита
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=short
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_DATE
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    # Получаем последний тег (если есть)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    
    # Проверяем, есть ли несохраненные изменения
    execute_process(
        COMMAND ${GIT_EXECUTABLE} diff-index --quiet HEAD --
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE GIT_HAS_CHANGES
    )
    
    if(GIT_HAS_CHANGES EQUAL 0)
        set(GIT_DIRTY "" PARENT_SCOPE)
    else()
        set(GIT_DIRTY "-dirty" PARENT_SCOPE)
    endif()
    
    # Устанавливаем значения в родительскую область видимости
    if(GIT_COMMIT_HASH)
        set(GIT_COMMIT_HASH "${GIT_COMMIT_HASH}${GIT_DIRTY}" PARENT_SCOPE)
    else()
        set(GIT_COMMIT_HASH "unknown" PARENT_SCOPE)
    endif()
    
    if(GIT_BRANCH)
        set(GIT_BRANCH "${GIT_BRANCH}" PARENT_SCOPE)
    else()
        set(GIT_BRANCH "unknown" PARENT_SCOPE)
    endif()
    
    if(GIT_COMMIT_DATE)
        set(GIT_COMMIT_DATE "${GIT_COMMIT_DATE}" PARENT_SCOPE)
    else()
        set(GIT_COMMIT_DATE "unknown" PARENT_SCOPE)
    endif()
    
    if(GIT_TAG)
        set(GIT_TAG "${GIT_TAG}" PARENT_SCOPE)
    else()
        set(GIT_TAG "unknown" PARENT_SCOPE)
    endif()
    
    # Выводим информацию для отладки
    message(STATUS "Git commit: ${GIT_COMMIT_HASH}")
    message(STATUS "Git branch: ${GIT_BRANCH}")
    message(STATUS "Git commit date: ${GIT_COMMIT_DATE}")
    if(NOT GIT_TAG STREQUAL "unknown")
        message(STATUS "Git tag: ${GIT_TAG}")
    endif()
endfunction()