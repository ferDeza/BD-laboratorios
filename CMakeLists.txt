cmake_minimum_required(VERSION 3.10)
project(Laboratorio1_BaseDatos2 CXX)

# Configuración del estándar C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

# Archivos fuente
set(SOURCES
    main.cpp
    Page.cpp
    part1_binary_files.cpp
    part2_memory_management.cpp
    part3_page_class.cpp
)

# Archivos header
set(HEADERS
    Page.h
)

# Crear ejecutable principal
add_executable(laboratorio1 ${SOURCES} ${HEADERS})

# Crear ejecutable de prueba
add_executable(quick_test quick_test.cpp Page.cpp)

# Opciones de compilación avanzadas
if(MSVC)
    # Para Visual Studio
    target_compile_options(laboratorio1 PRIVATE /W4 /EHsc)
    target_compile_options(quick_test PRIVATE /W4 /EHsc)
else()
    # Para gcc/clang
    target_compile_options(laboratorio1 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(quick_test PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Directorios de inclusión
target_include_directories(laboratorio1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(quick_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Propiedades del proyecto
set_target_properties(laboratorio1 PROPERTIES
    VERSION 1.0
    DESCRIPTION "Laboratorio 1 - Base de Datos II: Archivos Binarios y Gestión de Memoria"
)

# Instalación (opcional)
install(TARGETS laboratorio1 DESTINATION bin)
install(FILES README.md DOCUMENTACION.md DESTINATION doc)

# Custom targets
add_custom_target(clean_data
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/clean_data.cmake
    COMMENT "Limpiando archivos de datos generados..."
)

# Impresión de información
message(STATUS "Proyecto: Laboratorio 1 - Base de Datos II")
message(STATUS "Estándar C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compilador: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Modo: ${CMAKE_BUILD_TYPE}")
