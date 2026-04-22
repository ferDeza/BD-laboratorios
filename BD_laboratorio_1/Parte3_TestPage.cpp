#include <iostream>
#include <fstream>
#include "Page.h"

int main() {
    std::cout << "=== PARTE 3: CONCEPTO DE PAGINA ===" << std::endl;
    std::cout << std::endl;

    // 1. Crear páginas
    std::cout << "1. CREANDO PAGINAS:" << std::endl;
    
    Page page0(0);
    Page page1(1);
    Page page2(2);
    
    std::cout << "   Pagina 0 creada: ID = " << page0.getPageId() 
              << ", Tamanio = " << page0.getSize() << " bytes" << std::endl;
    std::cout << "   Pagina 1 creada: ID = " << page1.getPageId() 
              << ", Tamaño = " << page1.getSize() << " bytes" << std::endl;
    std::cout << "   Pagina 2 creada: ID = " << page2.getPageId() 
              << ", Tamanio = " << page2.getSize() << " bytes" << std::endl;
    std::cout << std::endl;

    // 2. Escribir datos en las páginas
    std::cout << "2. ESCRIBIENDO DATOS EN PAGINAS:" << std::endl;
    
    // Página 0: escribir texto "Hola"
    const char* text0 = "Hola";
    page0.writeData(text0, 0, 4);
    std::cout << "   Pagina 0: escrito '" << text0 << "' en offset 0" << std::endl;
    
    // Página 1: escribir números
    uint32_t number = 12345;
    page1.writeData(&number, 0, sizeof(uint32_t));
    std::cout << "   Pagina 1: escrito numero " << number 
              << " en offset 0" << std::endl;
    
    // Página 2: escribir en diferentes offsets
    const char* text2a = "Base";
    const char* text2b = "Datos";
    page2.writeData(text2a, 0, 4);
    page2.writeData(text2b, 100, 5);
    std::cout << "   Pagina 2: escrito '" << text2a << "' en offset 0" << std::endl;
    std::cout << "   Pagina 2: escrito '" << text2b << "' en offset 100" << std::endl;
    std::cout << std::endl;

    // 3. Leer datos de las páginas
    std::cout << "3. LEYENDO DATOS DE PAGINAS:" << std::endl;
    
    char buffer[100] = {0};
    
    page0.readData(buffer, 0, 4);
    std::cout << "   Pagina 0: leído '" << buffer << "'" << std::endl;
    
    uint32_t readNumber = 0;
    page1.readData(&readNumber, 0, sizeof(uint32_t));
    std::cout << "   Pagina 1: leído número " << readNumber << std::endl;
    
    char buffer2a[100] = {0};
    char buffer2b[100] = {0};
    page2.readData(buffer2a, 0, 4);
    page2.readData(buffer2b, 100, 5);
    std::cout << "   Pagina 2: leído '" << buffer2a << "' de offset 0" << std::endl;
    std::cout << "   Pagina 2: leído '" << buffer2b << "' de offset 100" << std::endl;
    std::cout << std::endl;

    // 4. Demostración de reset
    std::cout << "4. LIMPIANDO PAGINAS (RESET):" << std::endl;
    
    // Leer antes de limpiar
    char beforeReset[10] = {0};
    page2.readData(beforeReset, 0, 4);
    std::cout << "   Pagina 2 antes de reset: '" << beforeReset << "'" << std::endl;
    
    // Limpiar la página
    page2.reset();
    std::cout << "   Pagina 2 limpiada" << std::endl;
    
    // Leer después de limpiar
    char afterReset[10] = {0};
    page2.readData(afterReset, 0, 4);
    std::cout << "   Pagina 2 después de reset: (vacio)" << std::endl;
    std::cout << std::endl;

    // 5. Guardar una página en archivo
    std::cout << "5. GUARDANDO PAGINA EN ARCHIVO:" << std::endl;
    
    std::ofstream file("page_dump.bin", std::ios::binary);
    if (file) {
        uint8_t pageBuffer[PAGE_SIZE];
        page0.readData(pageBuffer, 0, PAGE_SIZE);
        file.write(reinterpret_cast<const char*>(pageBuffer), PAGE_SIZE);
        file.close();
        std::cout << "   Pagina 0 guardada en 'page_dump.bin' (" 
                  << PAGE_SIZE << " bytes)" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Prueba completada exitosamente!" << std::endl;

    return 0;
}
