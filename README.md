# Laboratorio 1 - Base de Datos II
## Archivos Binarios y Gestión de Memoria

Este proyecto implementa los tres ejercicios solicitados en el laboratorio de Base de Datos II:

### 📋 Contenido del Proyecto

#### **Parte 1: Manejo de Archivos Binarios**
- Crear archivo `data.db` con 10 páginas de 4 KB
- Escribir cada página con un patrón conocido
- Leer y verificar los datos escritos
- **Archivo principal**: `part1_binary_files.cpp`

#### **Parte 2: Gestión de Memoria en C++**
- Demostración de `new`/`delete` y `new[]`/`delete[]`
- Uso de `std::vector<uint8_t>` como buffer
- Rastreo de asignaciones para detectar memory leaks
- Análisis de padding y alineamiento en estructuras
- **Archivo principal**: `part2_memory_management.cpp`

#### **Parte 3: Concepto de Página**
- Implementación de clase `Page` de 4 KB
- Métodos: `writeData()`, `readData()`, `getPageId()`, `reset()`
- Manejo de errores con excepciones
- Demostración con múltiples páginas
- **Archivos**: `Page.h`, `Page.cpp`, `part3_page_class.cpp`

### 🛠️ Compilación

#### **Con Makefile (Recomendado)**
```bash
# En el directorio del proyecto
make                  # Compilar
make run              # Compilar y ejecutar
make clean            # Limpiar archivos objeto
make rebuild          # Limpiar y recompilar
```

#### **Con g++ manualmente**
```bash
g++ -std=c++11 -Wall -g main.cpp Page.cpp part1_binary_files.cpp \
    part2_memory_management.cpp part3_page_class.cpp -o laboratorio1
```

#### **Con Visual Studio (cl.exe) en Windows**
```cmd
cl.exe /EHsc /Fe"laboratorio1.exe" main.cpp Page.cpp part1_binary_files.cpp ^
    part2_memory_management.cpp part3_page_class.cpp
```

### ▶️ Ejecución

Después de compilar:
```bash
./laboratorio1          # Linux/Mac
laboratorio1.exe        # Windows
```

Se abrirá un menú interactivo con las siguientes opciones:
1. Ejecutar Parte 1 (Archivos Binarios)
2. Ejecutar Parte 2 (Gestión de Memoria)
3. Ejecutar Parte 3 (Clase Page)
4. Ejecutar Todas las Partes
0. Salir

### 📁 Estructura de Archivos

```
C:\Users\HP\Documents\C++\
├── Page.h                          # Declaración de clase Page
├── Page.cpp                        # Implementación de clase Page
├── main.cpp                        # Programa principal con menú
├── part1_binary_files.cpp          # Ejercicio 1: Archivos binarios
├── part2_memory_management.cpp     # Ejercicio 2: Gestión de memoria
├── part3_page_class.cpp            # Ejercicio 3: Clase Page
├── Makefile                        # Script de compilación
├── README.md                       # Este archivo
├── DOCUMENTACION.md                # Documentación detallada
└── data.db                         # Archivo binario (generado en ejecución)
```

### 🔍 Descripción de Archivos

| Archivo | Descripción |
|---------|-------------|
| `Page.h` | Definición de la clase Page con prototipos de métodos |
| `Page.cpp` | Implementación de la clase Page (almacenamiento 4 KB) |
| `main.cpp` | Menú interactivo principal que integra todas las partes |
| `part1_binary_files.cpp` | Creación de archivo `data.db` con 10 páginas |
| `part2_memory_management.cpp` | Demostración de new/delete, vectors, padding |
| `part3_page_class.cpp` | Pruebas de la clase Page con múltiples casos |
| `DOCUMENTACION.md` | Diccionario detallado de funciones y comandos |

### 📊 Resultados Esperados

#### Parte 1
- Crea archivo `data.db` (40 KB)
- Escribe 10 páginas, cada una con patrón único
- Verifica lectura correcta de datos

#### Parte 2
- Demuestra asignación/liberación de memoria
- Muestra padding en estructuras
- Verifica ausencia de memory leaks

#### Parte 3
- Crea instancias de Page de 4096 bytes
- Lee y escribe datos en posiciones específicas
- Demuestra reset y manejo de errores

### 💡 Conceptos Clave

**Página de Base de Datos**: Unidad fundamental de almacenamiento (4 KB)
- Minimiza accesos a disco
- Facilita gestión de buffer
- Base de todo DBMS

**Gestión de Memoria**: Critical en sistemas de bases de datos
- Evitar memory leaks
- Optimizar alineamiento
- Control de overhead

**Archivos Binarios**: Almacenamiento eficiente
- Compacto vs formato texto
- Acceso aleatorio rápido
- Estructura de datos serializada

### 📝 Diccionario de Comandos

Para una referencia completa de todas las funciones y comandos empleados,
consulte el archivo `DOCUMENTACION.md`.

### ⚙️ Requisitos

- **Compilador**: g++ o Visual Studio (C++11 o superior)
- **Sistema**: Windows, Linux, o macOS
- **Librerías**: STL (incluidas en compilador estándar)

### 🐛 Compiladores Probados

- ✅ g++ 9.0+ (MinGW en Windows)
- ✅ cl.exe (Visual Studio)
- ✅ clang++ (macOS)

### 📌 Notas

1. El archivo `data.db` se crea en el directorio de ejecución
2. La clase Page usa `std::vector` para gestión automática de memoria
3. Todos los métodos de Page validan entrada y lanzan excepciones
4. El menú permite ejecutar cada parte independientemente

### 📚 Lecturas Recomendadas

Para más información sobre los temas cubiertos:
1. "Database Management Systems" - Ramakrishnan & Gehrke
2. "The C++ Standard Library" - Nicolai M. Josuttis
3. "Advanced C++" - Scott Meyers

### 👤 Autor

Laboratorio de Base de Datos II
Curso: Base de Datos II
Año: 2024

---

**Última actualización**: 2024
**Versión**: 1.0
