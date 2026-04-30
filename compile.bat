@echo off
REM Script de compilación para Laboratorio 1 - Base de Datos II
REM Funciona con cl.exe (Visual Studio) y g++ (MinGW)

setlocal enabledelayedexpansion

echo.
echo ╔════════════════════════════════════════════════════╗
echo ║  Compilador para Laboratorio 1 - Base de Datos II  ║
echo ╚════════════════════════════════════════════════════╝
echo.

REM Detectar compilador disponible
where cl.exe >nul 2>nul
if !errorlevel! equ 0 (
    set COMPILER=cl
    echo [INFO] Detectado: Microsoft Visual C++ (cl.exe)
) else (
    where g++ >nul 2>nul
    if !errorlevel! equ 0 (
        set COMPILER=g++
        echo [INFO] Detectado: g++ (MinGW)
    ) else (
        echo [ERROR] No se encontró compilador (cl.exe o g++)
        pause
        exit /b 1
    )
)

echo.
echo [INFO] Compilador seleccionado: %COMPILER%
echo.

if "%1"=="" goto :menu
if /i "%1"=="clean" goto :clean
if /i "%1"=="build" goto :build
if /i "%1"=="run" goto :run
if /i "%1"=="rebuild" goto :rebuild

:menu
echo Opciones disponibles:
echo   compile.bat build    - Compilar proyecto
echo   compile.bat run      - Compilar y ejecutar
echo   compile.bat clean    - Limpiar archivos compilados
echo   compile.bat rebuild  - Limpiar y recompilar
echo.
set /p OPTION="Seleccione opción [build/run/clean/rebuild]: "

if /i "%OPTION%"=="build" goto :build
if /i "%OPTION%"=="run" goto :run
if /i "%OPTION%"=="clean" goto :clean
if /i "%OPTION%"=="rebuild" goto :rebuild
goto :menu

:build
echo.
echo [INFO] Compilando...
if "%COMPILER%"=="cl" (
    cl.exe /EHsc /Fe"laboratorio1.exe" ^
        main.cpp Page.cpp part1_binary_files.cpp ^
        part2_memory_management.cpp part3_page_class.cpp
    if !errorlevel! equ 0 (
        echo [SUCCESS] Compilación completada: laboratorio1.exe
    ) else (
        echo [ERROR] Error durante la compilación
        pause
        exit /b 1
    )
) else (
    g++ -std=c++11 -Wall -g ^
        main.cpp Page.cpp part1_binary_files.cpp ^
        part2_memory_management.cpp part3_page_class.cpp ^
        -o laboratorio1.exe
    if !errorlevel! equ 0 (
        echo [SUCCESS] Compilación completada: laboratorio1.exe
    ) else (
        echo [ERROR] Error durante la compilación
        pause
        exit /b 1
    )
)
pause
goto :end

:run
echo.
echo [INFO] Compilando...
if "%COMPILER%"=="cl" (
    cl.exe /EHsc /Fe"laboratorio1.exe" ^
        main.cpp Page.cpp part1_binary_files.cpp ^
        part2_memory_management.cpp part3_page_class.cpp
) else (
    g++ -std=c++11 -Wall -g ^
        main.cpp Page.cpp part1_binary_files.cpp ^
        part2_memory_management.cpp part3_page_class.cpp ^
        -o laboratorio1.exe
)

if !errorlevel! equ 0 (
    echo [SUCCESS] Compilación completada
    echo [INFO] Ejecutando...
    echo.
    laboratorio1.exe
) else (
    echo [ERROR] Error durante la compilación
    pause
    exit /b 1
)
goto :end

:clean
echo.
echo [INFO] Limpiando archivos compilados...
del /q *.exe 2>nul
del /q *.obj 2>nul
del /q *.ilk 2>nul
del /q *.pdb 2>nul
del /q data.db 2>nul
echo [SUCCESS] Archivos limpios
pause
goto :end

:rebuild
echo.
call :clean
goto :build

:end
endlocal
