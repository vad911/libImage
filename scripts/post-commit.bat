@echo off
rem post-commit hook for Windows (CMD/PowerShell environments)

for /f "delims=" %%i in ('git rev-parse --show-toplevel') do set PROJECT_DIR=%%i
set BUILD_DIR=%PROJECT_DIR%\build

echo [post-commit] Updating git_info.h...

if exist "%BUILD_DIR%" (
    cd "%BUILD_DIR%"
    
    rem Переконфигурируем проект
    cmake .. -DCMAKE_BUILD_TYPE=Release
    
    rem Если библиотека уже была собрана, пересобираем её
    if exist "CMakeCache.txt" (
        cmake --build . --target imageReader
    )
    
    echo [post-commit] git_info.h regenerated and library rebuilt.
) else (
    echo [post-commit] Build directory not found. Run CMake manually to generate build system.
)