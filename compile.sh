#!/bin/bash
# Script de compilación para Laboratorio 1 - Base de Datos II
# Uso: ./compile.sh [build|run|clean|rebuild]

set -e

echo ""
echo "╔════════════════════════════════════════════════════╗"
echo "║  Compilador para Laboratorio 1 - Base de Datos II  ║"
echo "╚════════════════════════════════════════════════════╝"
echo ""

# Variables de compilación
COMPILER="g++"
CXXFLAGS="-std=c++11 -Wall -Wextra -g"
SOURCES="main.cpp Page.cpp part1_binary_files.cpp part2_memory_management.cpp part3_page_class.cpp"
EXECUTABLE="laboratorio1"

# Detectar disponibilidad de compiladores
if ! command -v g++ &> /dev/null; then
    if command -v clang++ &> /dev/null; then
        COMPILER="clang++"
        echo "[INFO] g++ no encontrado, usando clang++"
    else
        echo "[ERROR] No se encontró compilador C++ (g++ o clang++)"
        exit 1
    fi
fi

echo "[INFO] Compilador: $COMPILER"
echo ""

# Función para compilar
build() {
    echo "[INFO] Compilando..."
    $COMPILER $CXXFLAGS -o $EXECUTABLE $SOURCES
    
    if [ $? -eq 0 ]; then
        echo "[SUCCESS] Compilación completada: $EXECUTABLE"
    else
        echo "[ERROR] Error durante la compilación"
        exit 1
    fi
}

# Función para ejecutar
run() {
    build
    echo "[INFO] Ejecutando..."
    echo ""
    ./$EXECUTABLE
}

# Función para limpiar
clean() {
    echo "[INFO] Limpiando archivos compilados..."
    rm -f $EXECUTABLE *.o *.a data.db core.*
    echo "[SUCCESS] Archivos limpios"
}

# Función para reconstruir
rebuild() {
    clean
    build
}

# Menú interactivo si no hay argumentos
if [ $# -eq 0 ]; then
    echo "Opciones disponibles:"
    echo "  ./compile.sh build    - Compilar proyecto"
    echo "  ./compile.sh run      - Compilar y ejecutar"
    echo "  ./compile.sh clean    - Limpiar archivos compilados"
    echo "  ./compile.sh rebuild  - Limpiar y recompilar"
    echo ""
    read -p "Seleccione opción [build/run/clean/rebuild]: " OPTION
else
    OPTION=$1
fi

case $OPTION in
    build)
        build
        ;;
    run)
        run
        ;;
    clean)
        clean
        ;;
    rebuild)
        rebuild
        ;;
    *)
        echo "[ERROR] Opción no válida"
        exit 1
        ;;
esac

echo ""
