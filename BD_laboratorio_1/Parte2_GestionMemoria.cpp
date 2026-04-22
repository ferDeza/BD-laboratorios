#include <iostream>
#include <vector>
#include <new>

const size_t PAGE_SIZE = 4096; // 4 KB

// Estructura simple para demostrar alineación
struct AlignedData {
    uint8_t byte1;      // 1 byte
    // padding aquí (normalmente)
    uint32_t int1;      // 4 bytes
    uint64_t long1;     // 8 bytes
};

// Estructura con alignas (C++11)
struct alignas(16) AlignedData16 {
    uint8_t byte1;
    uint32_t int1;
    uint64_t long1;
};

int main() {
    std::cout << "=== PARTE 2: MANEJO DE MEMORIA EN C++ ===" << std::endl;
    std::cout << std::endl;

    // 1. Demostración de tamaños y alineación
    std::cout << "1. ESTRUCTURAS Y ALINEACION:" << std::endl;
    std::cout << "   Tamanio de AlignedData: " << sizeof(AlignedData) << " bytes" << std::endl;
    std::cout << "   Tamanio de AlignedData16: " << sizeof(AlignedData16) << " bytes" << std::endl;
    std::cout << "   (AlignedData16 tiene alineacion de 16 bytes)" << std::endl;
    std::cout << std::endl;

    // 2. Reserva de memoria con new/delete
    std::cout << "2. RESERVA DE MEMORIA CON NEW/DELETE:" << std::endl;
    
    // Asignar memoria para un buffer de página
    uint8_t* pageBuffer = new uint8_t[PAGE_SIZE];
    std::cout << "   Asignados " << PAGE_SIZE << " bytes con new" << std::endl;
    
    // Llenar el buffer
    for (size_t i = 0; i < PAGE_SIZE; i++) {
        pageBuffer[i] = (i % 256);
    }
    std::cout << "   Buffer rellenado con datos" << std::endl;
    
    // Usar el buffer
    std::cout << "   Primeros 10 bytes: ";
    for (int i = 0; i < 10; i++) {
        std::cout << (int)pageBuffer[i] << " ";
    }
    std::cout << std::endl;
    
    // Liberar memoria
    delete[] pageBuffer;
    pageBuffer = nullptr; // Buena práctica: null después de delete
    std::cout << "   Memoria liberada con delete[]" << std::endl;
    std::cout << std::endl;

    // 3. Uso de std::vector como buffer de página (RECOMENDADO)
    std::cout << "3. USO DE std::vector COMO BUFFER:" << std::endl;
    
    std::vector<uint8_t> vectorBuffer(PAGE_SIZE);
    std::cout << "   Vector creado con " << vectorBuffer.size() << " bytes" << std::endl;
    std::cout << "   Capacidad: " << vectorBuffer.capacity() << " bytes" << std::endl;
    
    // Llenar el vector
    for (size_t i = 0; i < vectorBuffer.size(); i++) {
        vectorBuffer[i] = (i % 256);
    }
    std::cout << "   Vector rellenado" << std::endl;
    
    // El vector se libera automáticamente al salir del scope
    std::cout << "   (Se libera automaticamente - no hay memory leak)" << std::endl;
    std::cout << std::endl;

    // 4. Demostración de múltiples vectores (simulate un buffer pool)
    std::cout << "4. MULTIPLES PAGINAS (BUFFER POOL):" << std::endl;
    
    std::vector<std::vector<uint8_t>> pages;
    std::cout << "   Creando 5 páginas..." << std::endl;
    
    for (int i = 0; i < 5; i++) {
        std::vector<uint8_t> page(PAGE_SIZE);
        // Llenar cada página con su número
        for (size_t j = 0; j < PAGE_SIZE; j++) {
            page[j] = i;
        }
        pages.push_back(page);
        std::cout << "   Pagina " << i << " creada (" << page.size() << " bytes)" << std::endl;
    }
    std::cout << "   Total de paginas: " << pages.size() << std::endl;
    std::cout << "   Memoria total aproximada: " 
              << (pages.size() * PAGE_SIZE) << " bytes" << std::endl;
    
    // Acceder a una página
    std::cout << "   Accediendo a pagina 2, primer byte: " 
              << (int)pages[2][0] << std::endl;
    
    // Se libera automáticamente
    pages.clear();
    std::cout << " Paginas liberadas" << std::endl;
    std::cout << std::endl;

    // 5. Resumen
    std::cout << "5. RESUMEN - CONCEPTOS DEMOSTRACION:" << std::endl;
    std::cout << "Alineacion de datos (padding)" << std::endl;
    std::cout << "new/delete para memoria dinamica" << std::endl;
    std::cout << "std::vector como alternativa segura" << std::endl;
    std::cout << "Prevencion de memory leaks (nullptr)" << std::endl;
    std::cout << "Gestion automática de memoria con containers" << std::endl;

    return 0;
}
