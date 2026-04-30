#include <iostream>
#include <vector>
#include <iomanip>
#include <cstring>

/**
 * PARTE 2: MANEJO DE MEMORIA EN C++
 * 
 * OBJETIVO: Demostrar gestión de memoria con énfasis en:
 * - Reserva de memoria (new/delete)
 * - Uso de std::vector<uint8_t> como buffer de página
 * - Detección de memory leaks
 * - Estructuras alineadas (padding y alignment)
 * 
 * DICCIONARIO DE FUNCIONES Y COMANDOS:
 * 
 * 1. new - Operador para asignar memoria dinámica en el heap
 *    - Sintaxis: ptr = new Tipo(argumentos)
 *    - Retorna un puntero al objeto creado
 * 
 * 2. delete - Operador para liberar memoria asignada con new
 *    - Sintaxis: delete ptr;
 *    - Llama al destructor si es objeto
 * 
 * 3. delete[] - Operador para liberar arrays asignados con new[]
 *    - Sintaxis: delete[] arr;
 *    - Destruye cada elemento del array
 * 
 * 4. std::vector<T> - Contenedor dinámico de STL
 *    - Gestiona automáticamente la memoria
 *    - Métodos: resize(), reserve(), push_back(), clear()
 * 
 * 5. sizeof(T) - Obtiene el tamaño en bytes de un tipo o variable
 *    - Útil para analizar padding y alignment
 * 
 * 6. alignof(T) - Obtiene el alineamiento requerido en bytes (C++11)
 *    - Define múltiplos en memoria para optimización
 * 
 * 7. malloc/free - Asignación/liberación de memoria de bajo nivel
 *    - Alternativa a new/delete en C++
 * 
 * 8. std::cout - Salida estándar
 *    - Útil para rastrear asignación/liberación de memoria
 */

// Estructura de ejemplo para demostrar padding
struct SimpleStructUnaligned {
    char a;      // 1 byte
    int b;       // 4 bytes (puede tener padding antes)
    char c;      // 1 byte (puede tener padding después)
};

// Estructura alineada correctamente
struct SimpleStructAligned {
    int b;       // 4 bytes
    char a;      // 1 byte
    char c;      // 1 byte (los 2 bytes siguientes son padding)
};

// Estructura con alignas para controlar el alineamiento
struct __attribute__((aligned(16))) AlignedStructTo16 {
    int data;    // 4 bytes
};

class MemoryTracker {
private:
    static int allocCount;
    static int deallocCount;
    
public:
    static void* allocate(size_t size) {
        void* ptr = std::malloc(size);
        allocCount++;
        std::cout << "[ALLOC] Asignados " << size << " bytes. Total asignaciones: " 
                  << allocCount << std::endl;
        return ptr;
    }
    
    static void deallocate(void* ptr) {
        if (ptr != nullptr) {
            std::free(ptr);
            deallocCount++;
            std::cout << "[DEALLOC] Memoria liberada. Total liberaciones: " 
                      << deallocCount << std::endl;
        }
    }
    
    static void printSummary() {
        std::cout << "\n--- Resumen de Memoria ---" << std::endl;
        std::cout << "Total asignaciones: " << allocCount << std::endl;
        std::cout << "Total liberaciones: " << deallocCount << std::endl;
        if (allocCount == deallocCount) {
            std::cout << "Estado: SIN MEMORY LEAKS ✓" << std::endl;
        } else {
            std::cout << "ADVERTENCIA: Posible memory leak detectado!" << std::endl;
        }
    }
};

int MemoryTracker::allocCount = 0;
int MemoryTracker::deallocCount = 0;

void demonstrateNewDelete() {
    std::cout << "\n=== PARTE 2: MANEJO DE MEMORIA EN C++ ===" << std::endl;
    std::cout << "\n--- Demostración 1: new/delete ---" << std::endl;
    
    // Asignar memoria para un entero
    int* intPtr = new int(42);
    std::cout << "Asignada memoria para int: " << *intPtr << std::endl;
    delete intPtr;
    intPtr = nullptr;  // Buena práctica
    
    // Asignar memoria para un array
    int* arrayPtr = new int[5]{1, 2, 3, 4, 5};
    std::cout << "Array asignado: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arrayPtr[i] << " ";
    }
    std::cout << std::endl;
    delete[] arrayPtr;
    arrayPtr = nullptr;
}

void demonstrateVector() {
    std::cout << "\n--- Demostración 2: std::vector como buffer de página ---" << std::endl;
    
    const size_t PAGE_SIZE = 4096;
    
    // Vector auto-gestionado
    std::vector<uint8_t> pageBuffer(PAGE_SIZE);
    std::cout << "Vector creado de " << pageBuffer.size() << " bytes" << std::endl;
    std::cout << "Capacidad asignada: " << pageBuffer.capacity() << " bytes" << std::endl;
    
    // Llenar el buffer
    for (size_t i = 0; i < PAGE_SIZE; ++i) {
        pageBuffer[i] = static_cast<uint8_t>(i % 256);
    }
    
    std::cout << "Buffer llenado. Primeros 10 bytes: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << static_cast<int>(pageBuffer[i]) << " ";
    }
    std::cout << std::endl;
    
    // Vector se libera automáticamente al salir del scope
    std::cout << "Vector será destruido automáticamente al salir del scope\n" << std::endl;
}

void demonstrateMemoryTracker() {
    std::cout << "--- Demostración 3: Rastreo de asignación/liberación ---" << std::endl;
    
    // Asignar varios bloques
    void* ptr1 = MemoryTracker::allocate(256);
    void* ptr2 = MemoryTracker::allocate(512);
    void* ptr3 = MemoryTracker::allocate(1024);
    
    // Liberar bloques
    MemoryTracker::deallocate(ptr1);
    MemoryTracker::deallocate(ptr2);
    MemoryTracker::deallocate(ptr3);
    
    MemoryTracker::printSummary();
}

void demonstratePadding() {
    std::cout << "\n--- Demostración 4: Padding y Alignment en Estructuras ---" << std::endl;
    
    std::cout << "\nEstructura sin optimización de alineamiento:" << std::endl;
    std::cout << "  struct SimpleStructUnaligned { char a; int b; char c; }" << std::endl;
    std::cout << "  sizeof(SimpleStructUnaligned): " << sizeof(SimpleStructUnaligned) << " bytes" << std::endl;
    std::cout << "  alignof(SimpleStructUnaligned): " << alignof(SimpleStructUnaligned) << " bytes" << std::endl;
    
    SimpleStructUnaligned u;
    std::cout << "  Offset de 'a': " << offsetof(SimpleStructUnaligned, a) << std::endl;
    std::cout << "  Offset de 'b': " << offsetof(SimpleStructUnaligned, b) << std::endl;
    std::cout << "  Offset de 'c': " << offsetof(SimpleStructUnaligned, c) << std::endl;
    std::cout << "  Padding total: " << (sizeof(SimpleStructUnaligned) - sizeof(char) - sizeof(int) - sizeof(char)) 
              << " bytes" << std::endl;
    
    std::cout << "\nEstructura optimizada (reordenada):" << std::endl;
    std::cout << "  struct SimpleStructAligned { int b; char a; char c; }" << std::endl;
    std::cout << "  sizeof(SimpleStructAligned): " << sizeof(SimpleStructAligned) << " bytes" << std::endl;
    std::cout << "  alignof(SimpleStructAligned): " << alignof(SimpleStructAligned) << " bytes" << std::endl;
    
    SimpleStructAligned a;
    std::cout << "  Offset de 'b': " << offsetof(SimpleStructAligned, b) << std::endl;
    std::cout << "  Offset de 'a': " << offsetof(SimpleStructAligned, a) << std::endl;
    std::cout << "  Offset de 'c': " << offsetof(SimpleStructAligned, c) << std::endl;
    std::cout << "  Padding total: " << (sizeof(SimpleStructAligned) - sizeof(int) - sizeof(char) - sizeof(char)) 
              << " bytes\n" << std::endl;
}

int main_part2() {
    demonstrateNewDelete();
    demonstrateVector();
    demonstrateMemoryTracker();
    demonstratePadding();
    
    std::cout << "=== FIN PARTE 2 ===\n" << std::endl;
    return 0;
}
