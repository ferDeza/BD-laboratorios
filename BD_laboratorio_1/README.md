# Laboratorio Base de Datos II - Nro 01
## Manejo de Archivos y Gestión de Memoria

---

## Descripción General

Este laboratorio contiene 3 partes que cubren:
1. **Manejo de Archivos Binarios**: Crear y leer archivos binarios con páginas de 4 KB
2. **Gestión de Memoria en C++**: Demostración de new/delete, std::vector y alineación
3. **Concepto de Página**: Implementación de una clase `Page` para gestionar páginas de memoria

---

## Estructura de Archivos

```
BD laboratorio 1/
├── Parte1_ArchivosBinarios.cpp    # Programa 1: Creación de data.db
├── Parte2_GestionMemoria.cpp       # Programa 2: Demostración de memoria
├── Parte3_TestPage.cpp             # Programa 3: Pruebas de clase Page
├── Page.h                          # Header de la clase Page
├── Page.cpp                        # Implementación de la clase Page
├── Makefile                        # Archivo para compilar
├── DICCIONARIO_DATOS.md            # Documentación detallada
└── README.md                       # Este archivo
```

---

## Cómo Compilar

### Opción 1: Usar Makefile (Recomendado)

```bash
# Compilar todos los programas
make

# Ejecutar todos los programas
make run-all

# Limpiar archivos generados
make clean
```

### Opción 2: Compilación Manual

**Parte 1:**
```bash
g++ -std=c++11 -o Parte1.exe Parte1_ArchivosBinarios.cpp
```

**Parte 2:**
```bash
g++ -std=c++11 -o Parte2.exe Parte2_GestionMemoria.cpp
```

**Parte 3:**
```bash
g++ -std=c++11 -o Parte3.exe Parte3_TestPage.cpp Page.cpp
```

---

## Cómo Ejecutar

### Parte 1: Archivos Binarios
```bash
./Parte1.exe
```

**Qué hace:**
- Crea un archivo `data.db`
- Escribe 10 páginas de 4 KB
- Rellena cada página con su número de página
- Verifica la lectura del archivo
- Calcula el número total de páginas

**Salida esperada:**
```
=== PARTE 1: MANEJO DE ARCHIVOS BINARIOS ===

Creando archivo: data.db
Tamaño de página: 4096 bytes (4 KB)

Página 0 escrita: 4096 bytes
Página 1 escrita: 4096 bytes
...
Número de páginas: 10
```

---

### Parte 2: Gestión de Memoria
```bash
./Parte2.exe
```

**Qué demuestra:**
- Tamaños de estructuras y alineación (padding)
- Reserva de memoria con `new`/`delete`
- Uso seguro de `std::vector`
- Prevención de memory leaks
- Gestión automática de memoria

**Salida esperada:**
```
=== PARTE 2: MANEJO DE MEMORIA EN C++ ===

1. ESTRUCTURAS Y ALINEACION:
   Tamaño de AlignedData: 24 bytes
   Tamaño de AlignedData16: 32 bytes
   
2. RESERVA DE MEMORIA CON NEW/DELETE:
   Asignados 4096 bytes con new
   ...
```

---

### Parte 3: Clase Page
```bash
./Parte3.exe
```

**Qué demuestra:**
- Creación de páginas con identificadores
- Escritura de datos en diferentes offsets
- Lectura de datos desde las páginas
- Operación de reset (limpieza)
- Guardado de página en archivo binario

**Salida esperada:**
```
=== PARTE 3: CONCEPTO DE PAGINA ===

1. CREANDO PAGINAS:
   Página 0 creada: ID = 0, Tamaño = 4096 bytes
   Página 1 creada: ID = 1, Tamaño = 4096 bytes
   Página 2 creada: ID = 2, Tamaño = 4096 bytes
   
2. ESCRIBIENDO DATOS EN PAGINAS:
   Página 0: escrito 'Hola' en offset 0
   ...
```

---

## Archivos Generados por los Programas

Después de ejecutar los programas, se generarán:

| Archivo | Origen | Descripción |
|---------|--------|-------------|
| `data.db` | Parte 1 | Archivo binario con 10 páginas (40 KB) |
| `page_dump.bin` | Parte 3 | Dump de una página en formato binario |

---

## Detalles de Implementación

### Parte 1 - Archivo data.db
- **Tamaño total**: 40 KB (10 páginas × 4 KB)
- **Formato**: Binario
- **Patrón**: Cada página se rellena con su número de página (0-9)
- **Validación**: Se verifica la lectura

### Parte 2 - Conceptos de Memoria
- **Alineación**: Se demuestra padding y alineación explícita
- **new/delete**: Asignación y liberación de memoria
- **std::vector**: Alternativa segura recomendada
- **Memory Leaks**: Se evitan mediante nullptr y containers

### Parte 3 - Clase Page
- **Tamaño fijo**: 4096 bytes
- **Operaciones**: Lectura y escritura en cualquier offset
- **Seguridad**: Validación de límites
- **Reset**: Limpieza de toda la página

---

## Conceptos Clave

### Página (Page)
Unidad de almacenamiento de 4 KB. Es la estructura fundamental en sistemas de bases de datos.

### Buffer Binario
Vector de bytes (`std::vector<uint8_t>`) para almacenar datos sin interpretar.

### Offset
Posición dentro de la página donde se lee o escribe.

### Memory Leak
Memoria asignada que nunca se libera. Se previene usando std::vector.

### Alineación
Forma en que se distribuye la memoria para optimizar acceso. El padding es el espacio adicional.

---

## Notas Importantes

1. **Compatibilidad**: Código escrito en C++11 (compatible con compiladores modernos)
2. **Portabilidad**: Funciona en Windows, Linux y macOS
3. **Simplificidad**: Implementaciones simples pero funcionales
4. **Seguridad**: Se incluyen validaciones de límites y null pointers

---

## Diccionario de Datos

Para una documentación detallada de todas las funciones y comandos utilizados, consulte: **DICCIONARIO_DATOS.md**

---

## Autor
Laboratorio Base de Datos II - Nro 01

---
