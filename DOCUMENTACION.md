# LABORATORIO 1 - BASE DE DATOS II
## Documentación Técnica y Diccionario de Datos

---

## PARTE 1: MANEJO DE ARCHIVOS BINARIOS

### Objetivo
Crear un archivo "data.db" y escribir 10 páginas de 4 KB con un patrón conocido, demostrando operaciones de E/S binaria.

### Funciones y Comandos Empleados

#### 1. **std::ofstream** - Flujo de salida a archivo
```cpp
std::ofstream outFile("data.db", std::ios::binary);
```
- **Descripción**: Abre un archivo en modo escritura binaria
- **Parámetro 1**: Nombre del archivo
- **Parámetro 2**: Modo (std::ios::binary para archivos binarios)
- **Retorna**: Objeto que permite escribir en el archivo
- **Uso**: Crear y escribir archivos binarios

#### 2. **write()** - Escribir bloques de datos
```cpp
outFile.write(reinterpret_cast<const char*>(data.data()), PAGE_SIZE);
```
- **Descripción**: Escribe n bytes al archivo
- **Parámetro 1**: Puntero a buffer (convertido a const char*)
- **Parámetro 2**: Número de bytes a escribir
- **Retorna**: Referencia al stream para encadenamiento
- **Nota**: Utiliza reinterpret_cast para convertir tipos de punteros

#### 3. **tellp()** - Posición de escritura
```cpp
std::streampos position = outFile.tellp();
```
- **Descripción**: Obtiene la posición actual del puntero de escritura
- **Retorna**: streampos (posición en el archivo)
- **Uso**: Verificar dónde se está escribiendo en el archivo

#### 4. **seekg()** - Posicionar puntero de lectura
```cpp
inFile.seekg(pageNum * PAGE_SIZE);
```
- **Descripción**: Posiciona el puntero de lectura en una ubicación específica
- **Parámetro**: Posición en bytes desde el inicio
- **Uso**: Acceso aleatorio a datos en el archivo

#### 5. **std::ifstream** - Flujo de entrada desde archivo
```cpp
std::ifstream inFile("data.db", std::ios::binary);
```
- **Descripción**: Abre un archivo en modo lectura binaria
- **Parámetro 1**: Nombre del archivo
- **Parámetro 2**: Modo (std::ios::binary)
- **Retorna**: Objeto que permite leer del archivo

#### 6. **read()** - Leer bloques de datos
```cpp
inFile.read(reinterpret_cast<char*>(buffer.data()), PAGE_SIZE);
```
- **Descripción**: Lee n bytes del archivo al buffer
- **Parámetro 1**: Puntero a buffer destino
- **Parámetro 2**: Número de bytes a leer
- **Retorna**: Referencia al stream
- **Nota**: Utiliza reinterpret_cast para convertir tipos de punteros

#### 7. **gcount()** - Bytes leídos
```cpp
size_t bytesRead = inFile.gcount();
```
- **Descripción**: Retorna el número de bytes leídos en la última operación read()
- **Retorna**: streamsize (número de bytes leídos)
- **Uso**: Verificar si se leyeron los bytes esperados

#### 8. **is_open()** - Verificar si archivo está abierto
```cpp
if (!outFile.is_open()) { /* error */ }
```
- **Descripción**: Verifica si el archivo fue abierto exitosamente
- **Retorna**: bool (true si está abierto)
- **Uso**: Validación de errores

#### 9. **close()** - Cerrar archivo
```cpp
outFile.close();
```
- **Descripción**: Cierra el archivo y libera el recurso
- **Uso**: Garantizar que los datos se escriben correctamente

#### 10. **std::vector<uint8_t>** - Buffer dinámico
```cpp
std::vector<uint8_t> page(PAGE_SIZE);
```
- **Descripción**: Vector dinámico de bytes sin signo
- **Tamaño**: PAGE_SIZE (4096 bytes)
- **Ventajas**: Gestión automática de memoria

#### 11. **std::memcpy()** - Copiar memoria
```cpp
std::memcpy(dest, src, size);
```
- **Descripción**: Copia bloques de memoria
- **Parámetro 1**: Puntero destino
- **Parámetro 2**: Puntero origen
- **Parámetro 3**: Número de bytes a copiar
- **Uso**: Operaciones de E/S eficientes

#### 12. **reinterpret_cast** - Conversión de tipos de punteros
```cpp
reinterpret_cast<const char*>(data.data())
```
- **Descripción**: Convierte un puntero a otro tipo
- **Uso**: Necesario para pasar datos a métodos que esperan char*
- **Nota**: Cambios en la interpretación, no los datos

### Estructura de datos
```
data.db (40 KB total)
├─ Página 0: 4096 bytes (patrón: 0, 0, 0, ...)
├─ Página 1: 4096 bytes (patrón: 1, 1, 1, ...)
├─ Página 2: 4096 bytes (patrón: 2, 2, 2, ...)
│  ...
└─ Página 9: 4096 bytes (patrón: 9, 9, 9, ...)
```

---

## PARTE 2: GESTIÓN DE MEMORIA EN C++

### Objetivo
Demostrar asignación dinámica de memoria, buffers vectoriales, detección de memory leaks y alineamiento de estructuras.

### Funciones y Comandos Empleados

#### 1. **new** - Asignación dinámica de memoria
```cpp
int* ptr = new int(42);
int* arr = new int[5];
```
- **Descripción**: Asigna memoria en el heap y retorna un puntero
- **Para un objeto**: `new Tipo(argumentos)`
- **Para array**: `new Tipo[cantidad]`
- **Retorna**: Puntero al objeto/array creado
- **Ventajas**: Control total sobre el tiempo de vida del objeto

#### 2. **delete** - Liberar memoria de un objeto
```cpp
delete ptr;
ptr = nullptr;  // Buena práctica
```
- **Descripción**: Libera memoria asignada con new para un objeto
- **Importancia**: Previene memory leaks
- **Nota**: Llama al destructor si existe

#### 3. **delete[]** - Liberar memoria de un array
```cpp
delete[] arr;
```
- **Descripción**: Libera memoria de un array asignado con new[]
- **Crítico**: Usar delete[] en lugar de delete para arrays
- **Nota**: Llama al destructor para cada elemento

#### 4. **std::vector<T>** - Contenedor dinámico seguro
```cpp
std::vector<uint8_t> buffer(4096);
```
- **Descripción**: Contenedor de STL que gestiona automáticamente memoria
- **Ventajas**:
  - RAII (Resource Acquisition Is Initialization)
  - Copias seguras
  - Métodos útiles (resize, reserve, capacity)
  - Iteradores y range-based for loops

#### 5. **sizeof(T)** - Tamaño en bytes
```cpp
size_t size = sizeof(int);
```
- **Descripción**: Retorna el tamaño en bytes de un tipo
- **Uso**: Calcular requisitos de memoria
- **Nota**: Incluye padding en estructuras

#### 6. **alignof(T)** - Alineamiento requerido
```cpp
size_t alignment = alignof(int);  // generalmente 4
```
- **Descripción**: Retorna el alineamiento requerido en bytes (C++11)
- **Valores típicos**: 
  - char: 1 byte
  - int: 4 bytes
  - double: 8 bytes
  - punteros: 4 u 8 bytes
- **Uso**: Optimización de acceso a memoria

#### 7. **offsetof(Struct, member)** - Desplazamiento de campo
```cpp
size_t offset = offsetof(MyStruct, field);
```
- **Descripción**: Retorna el desplazamiento en bytes de un campo
- **Uso**: Analizar padding en estructuras
- **Fórmula**: Tamaño anterior + padding

#### 8. **std::fill()** - Llenar contenedor
```cpp
std::fill(data.begin(), data.end(), 0);
```
- **Descripción**: Rellena un rango con un valor
- **Parámetro 1-2**: Iteradores (inicio, fin)
- **Parámetro 3**: Valor para asignar
- **Alternativa**: memset() para datos sin procesar

#### 9. **std::malloc()** - Asignación de bajo nivel
```cpp
void* ptr = std::malloc(size);
```
- **Descripción**: Asigna memoria sin llamar constructores
- **Retorna**: Puntero void genérico
- **Uso**: Cuando necesitas control de bajo nivel
- **Nota**: Requiere std::free() para liberar

#### 10. **std::free()** - Liberar memoria malloc
```cpp
std::free(ptr);
```
- **Descripción**: Libera memoria asignada por malloc
- **Pairing**: Debe coincidir con malloc, no new
- **Nota**: No llama destructores

### Conceptos de Alineamiento

#### Padding (Relleno)
- **Definición**: Bytes no utilizados entre campos para alineamiento
- **Razón**: CPUs acceden más eficientemente a datos alineados
- **Ejemplo**:
  ```
  struct Unaligned {
    char a;        // offset 0 (1 byte)
    // 3 bytes padding
    int b;         // offset 4 (4 bytes)
    char c;        // offset 8 (1 byte)
    // 7 bytes padding
  }; // Total: 16 bytes (8 bytes wasted)
  
  struct Optimized {
    int b;         // offset 0 (4 bytes)
    char a;        // offset 4 (1 byte)
    char c;        // offset 5 (1 byte)
    // 2 bytes padding
  }; // Total: 8 bytes (2 bytes wasted)
  ```

#### Alineamiento de Atributos
```cpp
struct __attribute__((aligned(16))) AlignedTo16 {
    int data;
};  // Tamaño mínimo 16 bytes
```

### Memory Leak Detector
- **Propósito**: Rastrear asignaciones y liberaciones
- **Implementación**: Contador de malloc/free
- **Verificación**: allocCount == deallocCount → sin leaks

---

## PARTE 3: IMPLEMENTACIÓN DE CLASE PAGE

### Objetivo
Crear una clase `Page` que represente una página de 4 KB en memoria con operaciones de lectura/escritura.

### Especificaciones de la Clase

#### Atributos Privados
```cpp
private:
    std::vector<uint8_t> data;      // 4096 bytes
    page_id_t pageId;               // Identificador único
```

#### Métodos Públicos

##### 1. **Constructor: Page(page_id_t id = INVALID_PAGE_ID)**
```cpp
Page(page_id_t id = INVALID_PAGE_ID);
```
- **Descripción**: Inicializa una página nueva
- **Parámetro**: ID de la página (por defecto INVALID_PAGE_ID)
- **Acciones**:
  - Inicializa vector de 4096 bytes
  - Todos los bytes se establecen en 0
  - Asigna el pageId

##### 2. **writeData(const void* src, size_t offset, size_t len)**
```cpp
void writeData(const void* src, size_t offset, size_t len);
```
- **Descripción**: Escribe datos en la página
- **Parámetro 1**: Puntero a datos a escribir
- **Parámetro 2**: Desplazamiento en la página (en bytes)
- **Parámetro 3**: Número de bytes a escribir
- **Validaciones**:
  - src != nullptr
  - offset + len <= PAGE_SIZE
- **Implementación**: memcpy(data.data() + offset, src, len)
- **Excepciones**: 
  - std::invalid_argument si src es nullptr
  - std::out_of_range si sobrepasa límites

##### 3. **readData(void* dest, size_t offset, size_t len) const**
```cpp
void readData(void* dest, size_t offset, size_t len) const;
```
- **Descripción**: Lee datos de la página
- **Parámetro 1**: Puntero destino
- **Parámetro 2**: Desplazamiento en la página
- **Parámetro 3**: Número de bytes a leer
- **Validaciones**: Igual a writeData
- **Implementación**: memcpy(dest, data.data() + offset, len)
- **const**: No modifica el estado de la página

##### 4. **getPageId() const**
```cpp
page_id_t getPageId() const;
```
- **Descripción**: Obtiene el ID de la página
- **Retorna**: pageId
- **Uso**: Identificar páginas en buffer manager

##### 5. **reset()**
```cpp
void reset();
```
- **Descripción**: Limpia todos los datos de la página
- **Acción**: Llena todos los bytes con 0
- **Implementación**: std::fill(data.begin(), data.end(), 0)
- **Uso**: Preparar página para reutilización

##### 6. **getSize() const**
```cpp
size_t getSize() const;
```
- **Descripción**: Obtiene el tamaño de la página
- **Retorna**: PAGE_SIZE (4096)
- **Uso**: Consultas de tamaño

### Tipos Definidos
```cpp
typedef uint32_t page_id_t;              // ID de página de 32 bits
constexpr size_t PAGE_SIZE = 4096;       // Tamaño constante
constexpr page_id_t INVALID_PAGE_ID = 0xFFFFFFFF;  // ID inválida
```

### Diagrama de Memoria de Página
```
Página (4096 bytes total)
┌─────────────────────────────────────────┐
│  Offset 0-99: Reservado para metadata   │
├─────────────────────────────────────────┤
│  Offset 100-4095: Datos de usuario      │
│  ┌─────────┐  ┌──────────┐  ┌─────────┐│
│  │ Int     │  │ String   │  │ ...     ││
│  │ 4 bytes │  │ Variable │  │         ││
│  └─────────┘  └──────────┘  └─────────┘│
└─────────────────────────────────────────┘
```

### Caso de Uso: Buffer Manager
```cpp
// Crear un buffer de páginas
std::vector<Page> buffer;
for (int i = 0; i < 100; ++i) {
    buffer.push_back(Page(i));
}

// Escribir datos
buffer[0].writeData("data", 0, 4);

// Leer datos
char data[4];
buffer[0].readData(data, 0, 4);

// Limpiar página
buffer[0].reset();
```

---

## RESUMEN DE COMPILEACIÓN Y EJECUCIÓN

### Compilación con Makefile
```bash
make                # Compilar
make run            # Compilar y ejecutar
make clean          # Limpiar archivos objeto
make rebuild        # Limpiar y recompilar
```

### Compilación manual con g++
```bash
g++ -std=c++11 -Wall -g main.cpp Page.cpp part1_binary_files.cpp \
    part2_memory_management.cpp part3_page_class.cpp -o laboratorio1
```

### Ejecución
```bash
./laboratorio1
```

---

## ARCHIVOS DEL PROYECTO

```
C++ Workspace/
├── Page.h                      # Declaración de clase Page
├── Page.cpp                    # Implementación de clase Page
├── main.cpp                    # Programa principal con menú
├── part1_binary_files.cpp      # Ejercicio Parte 1
├── part2_memory_management.cpp # Ejercicio Parte 2
├── part3_page_class.cpp        # Ejercicio Parte 3
├── Makefile                    # Script de compilación
├── README.md                   # Este archivo
└── data.db                     # Archivo binario generado (creado en ejecución)
```

---

## NOTAS IMPORTANTES

1. **Gestión de Memoria**: 
   - Toda memoria asignada con `new` debe liberarse con `delete`
   - Usar `std::vector` siempre que sea posible
   - Verificar memory leaks con herramientas como Valgrind

2. **Alineamiento**:
   - Ordenar campos de mayor a menor tamaño reduce padding
   - Típicamente alineamiento = máximo tamaño de campo

3. **Archivos Binarios**:
   - Usar siempre std::ios::binary para archivos binarios
   - Convertir punteros con reinterpret_cast cuando sea necesario
   - Validar que los archivos se abran correctamente

4. **Clase Page**:
   - Representa una unidad fundamental de almacenamiento
   - Forma la base de un Buffer Manager en DBMS
   - Proporciona abstracción para E/S en disco

---

Documento generado: 2024
Laboratorio: Base de Datos II
Tema: Archivos Binarios y Gestión de Memoria
