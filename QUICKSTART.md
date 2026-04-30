# GUÍA DE INICIO RÁPIDO
## Laboratorio 1 - Base de Datos II

### 🎯 Resumen de lo que contiene este proyecto

Este proyecto implementa completamente los 3 ejercicios del laboratorio:

| Parte | Tema | Archivos |
|-------|------|----------|
| **1** | Manejo de Archivos Binarios | `part1_binary_files.cpp` |
| **2** | Gestión de Memoria en C++ | `part2_memory_management.cpp` |
| **3** | Clase Page (4 KB) | `Page.h`, `Page.cpp`, `part3_page_class.cpp` |

---

## ⚡ Inicio Rápido (5 minutos)

### 1️⃣ **En Windows (con compile.bat)**
```cmd
compile.bat run
```
O simplemente:
```cmd
compile.bat
```
Y selecciona "run" del menú

### 2️⃣ **En Linux/Mac (con compile.sh)**
```bash
chmod +x compile.sh
./compile.sh run
```
O simplemente:
```bash
./compile.sh
```
Y selecciona "run" del menú

### 3️⃣ **Con CMake (recomendado para proyectos grandes)**
```bash
mkdir build
cd build
cmake ..
cmake --build .
./laboratorio1
```

### 4️⃣ **Con Makefile**
```bash
make run
```

---

## 📋 Archivos Creados

```
📦 C++ Workspace
├── 📄 main.cpp                      ← Menú principal
├── 📄 Page.h                        ← Definición clase Page
├── 📄 Page.cpp                      ← Implementación Page
├── 📄 part1_binary_files.cpp        ← Ejercicio 1
├── 📄 part2_memory_management.cpp   ← Ejercicio 2
├── 📄 part3_page_class.cpp          ← Ejercicio 3
├── 📄 quick_test.cpp                ← Pruebas unitarias
├── 🛠️  Makefile                      ← Build Linux/Mac
├── 🛠️  CMakeLists.txt               ← Build moderno
├── 🛠️  compile.bat                  ← Build Windows
├── 🛠️  compile.sh                   ← Build Linux/Mac
├── 📖 README.md                     ← Documentación principal
└── 📖 DOCUMENTACION.md              ← Diccionario detallado
```

---

## 📊 ¿Qué hace cada parte?

### **PARTE 1: Archivos Binarios**
✅ Crea archivo `data.db` (40 KB)
✅ Escribe 10 páginas de 4 KB cada una
✅ Cada página contiene un patrón único (número de página)
✅ Lee y verifica los datos correctamente

**Comando en el menú**: Opción 1

### **PARTE 2: Gestión de Memoria**
✅ Demuestra `new`/`delete` para objetos
✅ Demuestra `new[]`/`delete[]` para arrays
✅ Usa `std::vector<uint8_t>` como buffer seguro
✅ Analiza padding en estructuras
✅ Rastrea asignaciones para detectar memory leaks

**Comando en el menú**: Opción 2

### **PARTE 3: Clase Page**
✅ Crea instancias de Page (4096 bytes)
✅ Demuestra `writeData()` - escribir en posición específica
✅ Demuestra `readData()` - leer desde posición específica
✅ Demuestra `reset()` - limpiar página
✅ Manejo de errores con excepciones
✅ Prueba con múltiples páginas

**Comando en el menú**: Opción 3

---

## 🧪 Pruebas Rápidas

### Verificar que todo funciona:
```bash
# Compilar y ejecutar tests unitarios
g++ -std=c++11 quick_test.cpp Page.cpp -o test
./test
```

---

## 📝 Estructura de la Clase Page

```cpp
class Page {
private:
    std::vector<uint8_t> data;    // 4096 bytes
    page_id_t pageId;             // ID única

public:
    Page(page_id_t id);
    void writeData(const void* src, size_t offset, size_t len);
    void readData(void* dest, size_t offset, size_t len) const;
    page_id_t getPageId() const;
    void reset();
    size_t getSize() const;
};
```

---

## 🔧 Opciones de Compilación

| Método | Comando | Plataforma |
|--------|---------|-----------|
| **Makefile** | `make run` | Linux/Mac |
| **Bash** | `./compile.sh run` | Linux/Mac |
| **Batch** | `compile.bat run` | Windows |
| **CMake** | `cmake .. && make` | Multiplataforma |
| **Manual g++** | `g++ -std=c++11 ... -o lab1` | Cualquiera |
| **Manual cl.exe** | `cl.exe /EHsc ...` | Windows |

---

## 💾 Archivos Generados

Durante la ejecución se crean:

- `data.db` - Archivo binario con 10 páginas
- `laboratorio1.exe` o `laboratorio1` - Ejecutable principal
- Archivos objeto `.obj` o `.o` (si usas compilación manual)

Para limpiar:
```bash
make clean          # Con Makefile
./compile.sh clean  # Con script bash
compile.bat clean   # Con script batch
```

---

## 🎓 Conceptos Clave Implementados

### Archivos Binarios
- Modo `std::ios::binary`
- Escritura con `write()`
- Lectura con `read()`
- Posicionamiento con `seekg()` y `seekp()`

### Gestión de Memoria
- Asignación con `new`/`new[]`
- Liberación con `delete`/`delete[]`
- Contenedores `std::vector` seguros
- Análisis de padding y alineamiento

### Conceptos de BD
- **Página**: Unidad fundamental (4 KB)
- **Buffer**: Almacenamiento en memoria
- **E/S**: Lectura/escritura desde disco
- **Serialización**: Almacenamiento de datos

---

## 📚 Archivo de Documentación

Para referencia completa de TODAS las funciones:

📖 **DOCUMENTACION.md** - Contiene:
- Diccionario detallado de funciones
- Ejemplos de uso
- Explicaciones de conceptos
- Descripciones de parámetros

---

## ✅ Validación

El proyecto incluye:
- ✓ Código compilable y funcional
- ✓ Manejo de errores con excepciones
- ✓ Documentación completa
- ✓ Ejemplos de uso
- ✓ Scripts de compilación para múltiples plataformas
- ✓ Pruebas unitarias incluidas

---

## 🚀 Próximos Pasos

1. **Compilar**: Usa uno de los métodos arriba
2. **Ejecutar**: Selecciona la parte que desees probar
3. **Revisar**: Mira la salida y entiende lo que hace
4. **Estudiar**: Lee DOCUMENTACION.md para detalles
5. **Extender**: Agrega tus propias pruebas

---

## 💡 Tips

- El archivo `data.db` se crea en el directorio actual
- Usa `quick_test.cpp` para validar que todo compila
- Revisa los comentarios en cada archivo fuente
- DOCUMENTACION.md tiene toda la información técnica

---

## ❓ Preguntas Frecuentes

**P: ¿Qué compilador debo usar?**
A: g++ en Linux/Mac, cl.exe en Windows, o clang++ en cualquier lado

**P: ¿Qué versión de C++?**
A: C++11 o superior (el código usa características básicas)

**P: ¿Qué archivo ejecuto primero?**
A: Compila con `make run` o `compile.bat run` y selecciona del menú

**P: ¿Dónde se guarda data.db?**
A: En el directorio donde ejecutas el programa

**P: ¿Hay memory leaks?**
A: No, el código usa std::vector para gestión automática

---

## 📞 Soporte

Para problemas:
1. Verifica que tienes un compilador C++ instalado
2. Lee DOCUMENTACION.md para entender cada función
3. Ejecuta quick_test.cpp para validar instalación
4. Revisa los comentarios en el código fuente

---

**Última actualización**: 2024
**Versión del Lab**: 1.0
**Requisito**: C++11 o superior
