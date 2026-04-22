


# LABORATORIO BASE DE DATOS II - Nro 01
## Documentación: Diccionario de Datos

---

## PARTE 1: MANEJO DE ARCHIVOS BINARIOS

### Objetivo
Crear un archivo "data.db" y escribir 10 páginas de 4 KB con un patrón conocido.

### Funciones y Comandos Empleados

| Función/Comando | Descripción | Parámetros | Retorno |
|---|---|---|---|
| `std::ofstream` | Abre un archivo para escritura en modo binario | `filename, std::ios::binary` | Stream de salida |
| `std::ifstream` | Abre un archivo para lectura en modo binario | `filename, std::ios::binary` | Stream de entrada |
| `file.write()` | Escribe bloque de datos en el archivo | `(const char* ptr, size_t count)` | void |
| `file.read()` | Lee bloque de datos del archivo | `(char* ptr, size_t count)` | void |
| `seekg()` | Posiciona puntero de lectura en el archivo | `(offset, modo)` | void |
| `seekp()` | Posiciona puntero de escritura en el archivo | `(offset, modo)` | void |
| `tellg()` | Obtiene posición actual de lectura | - | streampos |
| `tellp()` | Obtiene posición actual de escritura | - | streampos |
| `std::vector<uint8_t>` | Vector para almacenar página en memoria | `(size_t size)` | contenedor |
| `file.close()` | Cierra el archivo | - | void |

### Constantes Utilizadas
- `PAGE_SIZE = 4096` bytes (4 KB)
- Número de páginas: 10
- Patrón de relleno: número de página (0-9)

### Variables Principales
- `filename`: Nombre del archivo ("data.db")
- `page`: Vector de bytes para cada página
- `fileSize`: Tamaño total del archivo
- `numPages`: Número de páginas calculado

---

## PARTE 2: MANEJO DE MEMORIA EN C++

### Objetivo
Demostrar conceptos de gestión de memoria incluyendo alineación, new/delete y std::vector.

### Funciones y Comandos Empleados

| Función/Comando | Descripción | Parámetros | Retorno |
|---|---|---|---|
| `new` | Asigna memoria dinámica | `[[] size_t quantity` | Puntero |
| `delete[]` | Libera memoria dinámica (arrays) | `pointer` | void |
| `std::vector<T>` | Contenedor dinámico seguro | `size_t initial_size` | contenedor |
| `vector.size()` | Obtiene tamaño del vector | - | size_t |
| `vector.capacity()` | Obtiene capacidad asignada | - | size_t |
| `vector.push_back()` | Agrega elemento al final | `const T& value` | void |
| `vector.clear()` | Vacía el contenedor | - | void |
| `vector.data()` | Obtiene puntero a datos | - | T* |
| `std::fill()` | Rellena rango con valor | `(begin, end, value)` | void |
| `sizeof()` | Obtiene tamaño de tipo | `type` | size_t |
| `__attribute__((aligned(n)))` | Especifica alineación en bytes | `n` | - |
| `reinterpret_cast<>` | Conversión de tipos de puntero | `<new_type>(expr)` | new_type |

### Conceptos Demostrados

1. **Alineación (Padding)**
   - `AlignedData`: Estructura con padding automático
   - `AlignedData16`: Estructura con alineación explícita a 16 bytes

2. **Reserva con new/delete**
   - Asignación: `uint8_t* ptr = new uint8_t[4096]`
   - Liberación: `delete[] ptr`
   - Buena práctica: `ptr = nullptr` después de delete

3. **std::vector (Recomendado)**
   - Gestión automática de memoria
   - No requiere delete manual
   - Más seguro contra memory leaks

### Variables Principales
- `pageBuffer`: Puntero a memoria asignada con new
- `vectorBuffer`: Vector para almacenar página
- `pages`: Vector de vectores (buffer pool)
- `AlignedData`, `AlignedData16`: Estructuras para demostrar alineación

---

## PARTE 3: CONCEPTO DE PÁGINA

### Objetivo
Implementar una clase `Page` con funcionalidades de lectura/escritura de datos.

### Clase Page - Métodos

| Método | Descripción | Parámetros | Retorno |
|---|---|---|---|
| `Page(page_id_t id)` | Constructor | `id = INVALID_PAGE_ID` | - |
| `writeData()` | Escribe datos en página | `(src, offset, len)` | void |
| `readData()` | Lee datos de página | `(dest, offset, len)` | void |
| `getPageId()` | Obtiene ID de página | - | page_id_t |
| `getSize()` | Obtiene tamaño de página | - | size_t |
| `reset()` | Limpia página (llena con 0) | - | void |

### Funciones Auxiliares de la Clase

| Función | Descripción | Uso |
|---|---|---|
| `std::memcpy()` | Copia memoria | Lectura y escritura de datos |
| `std::fill()` | Rellena rango | Reset de página |

### Constantes y Tipos

| Constante | Valor | Descripción |
|---|---|---|
| `PAGE_SIZE` | 4096 | Tamaño de página en bytes |
| `INVALID_PAGE_ID` | 0xFFFFFFFF | ID inválida (4294967295) |
| `page_id_t` | uint32_t | Tipo para ID de página |

### Miembros Privados de Page

| Miembro | Tipo | Descripción |
|---|---|---|
| `data` | std::vector<uint8_t> | Buffer de 4096 bytes |
| `pageId` | page_id_t | Identificador único de la página |

### Validaciones Implementadas

1. **Límites de escritura**: offset + len <= PAGE_SIZE
2. **Límites de lectura**: offset + len <= PAGE_SIZE
3. **Validación de punteros**: Verificar que src/dest no sean nullptr

---

## RESUMEN DE ARCHIVOS GENERADOS

| Archivo | Descripción | Tipo |
|---|---|---|
| `Parte1_ArchivosBinarios.cpp` | Programa para crear data.db | Implementación |
| `Parte2_GestionMemoria.cpp` | Programa de demostración de memoria | Implementación |
| `Page.h` | Definición de clase Page | Header |
| `Page.cpp` | Implementación de clase Page | Implementación |
| `Parte3_TestPage.cpp` | Pruebas de la clase Page | Programa principal |
| `data.db` | Archivo binario generado (Parte 1) | Datos |
| `page_dump.bin` | Página guardada en archivo (Parte 3) | Datos |

---

## COMPILACIÓN Y EJECUCIÓN

### Compilación de Parte 1
```bash
g++ -o Parte1.exe Parte1_ArchivosBinarios.cpp
./Parte1.exe
```

### Compilación de Parte 2
```bash
g++ -o Parte2.exe Parte2_GestionMemoria.cpp
./Parte2.exe
```

### Compilación de Parte 3
```bash
g++ -o Parte3.exe Parte3_TestPage.cpp Page.cpp
./Parte3.exe
```

---

## NOTAS IMPORTANTES

1. **Tamaño de Página**: Todas las implementaciones usan 4096 bytes (4 KB)
2. **Memory Safety**: Se utilizó std::vector donde es posible para evitar memory leaks
3. **Portabilidad**: El código es compatible con C++11 y superiores
4. **Error Handling**: Se incluyen validaciones básicas de límites

---
