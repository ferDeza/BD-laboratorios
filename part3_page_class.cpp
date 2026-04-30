#include "Page.h"
#include <iostream>
#include <cstring>

/**
 * PARTE 3: CONCEPTO DE PÁGINA
 * 
 * Demostración de la clase Page que representa una página de 4096 bytes
 * 
 * Funcionalidades demostradas:
 * - Creación de páginas
 * - Escritura y lectura de datos
 * - Gestión de identificadores de página
 * - Limpieza de páginas
 */

void demonstratePageClass() {
    std::cout << "\n=== PARTE 3: CONCEPTO DE PÁGINA ===" << std::endl;
    
    // Crear una página con ID 1
    Page page1(1);
    std::cout << "\nPágina creada con ID: " << page1.getPageId() << std::endl;
    std::cout << "Tamaño de página: " << page1.getSize() << " bytes" << std::endl;
    
    // Escribir datos en la página
    std::cout << "\n--- Escribiendo datos en la página ---" << std::endl;
    
    const char* message = "Hello, Database!";
    page1.writeData(message, 0, std::strlen(message) + 1);
    std::cout << "Mensaje escrito en posición 0: \"" << message << "\"" << std::endl;
    
    // Escribir datos en otra posición
    int data = 12345;
    page1.writeData(&data, 100, sizeof(int));
    std::cout << "Número entero escrito en posición 100: " << data << std::endl;
    
    // Escribir array de datos
    uint8_t pattern[] = {0xFF, 0xAA, 0x55, 0x00};
    page1.writeData(pattern, 200, sizeof(pattern));
    std::cout << "Patrón de bytes escrito en posición 200" << std::endl;
    
    // Leer datos de la página
    std::cout << "\n--- Leyendo datos de la página ---" << std::endl;
    
    char readMessage[50] = {0};
    page1.readData(readMessage, 0, std::strlen(message) + 1);
    std::cout << "Mensaje leído: \"" << readMessage << "\"" << std::endl;
    
    int readData = 0;
    page1.readData(&readData, 100, sizeof(int));
    std::cout << "Número leído: " << readData << std::endl;
    
    uint8_t readPattern[4] = {0};
    page1.readData(readPattern, 200, sizeof(readPattern));
    std::cout << "Patrón leído: 0x" << std::hex;
    for (uint8_t byte : readPattern) {
        std::cout << static_cast<int>(byte) << " ";
    }
    std::cout << std::dec << std::endl;
    
    // Demostración con múltiples páginas
    std::cout << "\n--- Trabajando con múltiples páginas ---" << std::endl;
    
    Page pages[5];
    for (int i = 0; i < 5; ++i) {
        pages[i] = Page(i);
        
        // Llenar cada página con un patrón diferente
        std::vector<uint8_t> fillPattern(256, static_cast<uint8_t>(i * 50));
        pages[i].writeData(fillPattern.data(), 0, fillPattern.size());
        
        std::cout << "Página " << i << " creada y llenada" << std::endl;
    }
    
    // Reset de página
    std::cout << "\n--- Reset de página ---" << std::endl;
    
    char testData[20];
    pages[0].readData(testData, 0, sizeof(testData));
    std::cout << "Datos en página 0 antes del reset: " 
              << static_cast<int>(testData[0]) << std::endl;
    
    pages[0].reset();
    std::cout << "Página 0 reseteada (llenada con ceros)" << std::endl;
    
    pages[0].readData(testData, 0, sizeof(testData));
    bool allZeros = true;
    for (char c : testData) {
        if (c != 0) allZeros = false;
    }
    std::cout << "Todos los bytes son cero después del reset: " 
              << (allZeros ? "SÍ" : "NO") << std::endl;
    
    // Manejo de errores
    std::cout << "\n--- Manejo de errores ---" << std::endl;
    
    try {
        // Intentar escribir fuera de los límites
        Page errorPage(99);
        uint8_t largeData[5000];
        errorPage.writeData(largeData, 0, 5000);
    } catch (const std::out_of_range& e) {
        std::cout << "Error capturado (esperado): Intento de escribir fuera de límites" << std::endl;
    }
    
    try {
        // Intentar usar puntero nulo
        Page errorPage2(100);
        errorPage2.writeData(nullptr, 0, 100);
    } catch (const std::invalid_argument& e) {
        std::cout << "Error capturado (esperado): Puntero nulo proporcionado" << std::endl;
    }
    
    std::cout << "\n=== FIN PARTE 3 ===\n" << std::endl;
}

int main_part3() {
    demonstratePageClass();
    return 0;
}
