/**
 * QUICK_TEST.CPP
 * Programa de prueba rápida para validar que todo compila y funciona
 * Puede compilarse independientemente para verificación rápida
 * 
 * Compilación:
 *   g++ -std=c++11 quick_test.cpp Page.cpp -o quick_test
 *   ./quick_test
 */

#include "Page.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <cstring>

int testsRun = 0;
int testsPassed = 0;

#define TEST(condition, message) \
    do { \
        testsRun++; \
        if (condition) { \
            testsPassed++; \
            std::cout << "[PASS] " << message << std::endl; \
        } else { \
            std::cout << "[FAIL] " << message << std::endl; \
        } \
    } while(0)

void testPageConstruction() {
    std::cout << "\n=== Test: Construcción de Page ===" << std::endl;
    
    Page page1;
    TEST(page1.getPageId() == INVALID_PAGE_ID, "Page sin ID por defecto");
    
    Page page2(42);
    TEST(page2.getPageId() == 42, "Page con ID específico");
    
    TEST(page1.getSize() == PAGE_SIZE, "Tamaño de página correcto");
}

void testPageWrite() {
    std::cout << "\n=== Test: Escritura en Page ===" << std::endl;
    
    Page page(1);
    
    // Escribir bytes simples
    uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    page.writeData(data, 0, sizeof(data));
    
    uint8_t readData[4];
    page.readData(readData, 0, sizeof(readData));
    
    bool correctData = true;
    for (int i = 0; i < 4; ++i) {
        if (readData[i] != data[i]) correctData = false;
    }
    TEST(correctData, "Escritura y lectura de bytes simples");
    
    // Escribir en diferentes posiciones
    int intValue = 123456;
    page.writeData(&intValue, 100, sizeof(int));
    
    int readInt;
    page.readData(&readInt, 100, sizeof(int));
    TEST(readInt == intValue, "Escritura en posición específica");
}

void testPageReset() {
    std::cout << "\n=== Test: Reset de Page ===" << std::endl;
    
    Page page(2);
    
    // Escribir datos
    uint8_t pattern[10];
    for (int i = 0; i < 10; ++i) pattern[i] = 0xFF;
    page.writeData(pattern, 0, sizeof(pattern));
    
    // Reset
    page.reset();
    
    // Verificar que todo es cero
    uint8_t zeroCheck[10];
    page.readData(zeroCheck, 0, sizeof(zeroCheck));
    
    bool allZeros = true;
    for (int i = 0; i < 10; ++i) {
        if (zeroCheck[i] != 0) allZeros = false;
    }
    TEST(allZeros, "Reset limpia todos los bytes");
}

void testMultiplePages() {
    std::cout << "\n=== Test: Múltiples páginas ===" << std::endl;
    
    const int NUM_PAGES = 5;
    Page pages[NUM_PAGES];
    
    // Inicializar cada página con patrón único
    for (int i = 0; i < NUM_PAGES; ++i) {
        pages[i] = Page(i);
        uint8_t pattern = static_cast<uint8_t>(i * 50);
        pages[i].writeData(&pattern, 0, 1);
    }
    
    // Verificar
    bool pagesOK = true;
    for (int i = 0; i < NUM_PAGES; ++i) {
        uint8_t readValue;
        pages[i].readData(&readValue, 0, 1);
        if (readValue != static_cast<uint8_t>(i * 50)) {
            pagesOK = false;
        }
    }
    TEST(pagesOK, "Múltiples páginas independientes");
}

void testBinaryFile() {
    std::cout << "\n=== Test: Archivo binario ===" << std::endl;
    
    const char* filename = "test_data.db";
    const int NUM_PAGES = 3;
    const size_t PAGE_SIZE_TEST = 4096;
    
    // Crear archivo
    {
        std::ofstream file(filename, std::ios::binary);
        for (int i = 0; i < NUM_PAGES; ++i) {
            std::vector<uint8_t> page(PAGE_SIZE_TEST, static_cast<uint8_t>(i));
            file.write(reinterpret_cast<const char*>(page.data()), PAGE_SIZE_TEST);
        }
    }
    
    // Leer y verificar
    std::ifstream file(filename, std::ios::binary);
    bool fileOK = true;
    for (int i = 0; i < NUM_PAGES; ++i) {
        std::vector<uint8_t> page(PAGE_SIZE_TEST);
        file.read(reinterpret_cast<char*>(page.data()), PAGE_SIZE_TEST);
        
        if (file.gcount() != static_cast<int>(PAGE_SIZE_TEST)) {
            fileOK = false;
            break;
        }
        
        for (size_t j = 0; j < PAGE_SIZE_TEST; ++j) {
            if (page[j] != static_cast<uint8_t>(i)) {
                fileOK = false;
                break;
            }
        }
    }
    file.close();
    
    // Limpiar
    std::remove(filename);
    
    TEST(fileOK, "Operaciones de archivo binario");
}

void testErrorHandling() {
    std::cout << "\n=== Test: Manejo de errores ===" << std::endl;
    
    Page page(3);
    bool exceptionCaught = false;
    
    // Test 1: Escribir fuera de límites
    try {
        uint8_t largeData[5000];
        page.writeData(largeData, 0, 5000);
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    TEST(exceptionCaught, "Excepción por escribir fuera de límites");
    
    // Test 2: Puntero nulo
    exceptionCaught = false;
    try {
        page.writeData(nullptr, 0, 10);
    } catch (const std::invalid_argument&) {
        exceptionCaught = true;
    }
    TEST(exceptionCaught, "Excepción por puntero nulo");
    
    // Test 3: Lectura fuera de límites
    exceptionCaught = false;
    try {
        uint8_t buffer[5000];
        page.readData(buffer, 0, 5000);
    } catch (const std::out_of_range&) {
        exceptionCaught = true;
    }
    TEST(exceptionCaught, "Excepción por leer fuera de límites");
}

void testMemoryManagement() {
    std::cout << "\n=== Test: Gestión de memoria ===" << std::endl;
    
    // Verificar que vector se gestiona correctamente
    {
        std::vector<uint8_t> buffer(4096, 0xFF);
        TEST(buffer.size() == 4096, "Vector con tamaño correcto");
        TEST(buffer.capacity() >= 4096, "Vector con capacidad suficiente");
    } // Vector se destruye automáticamente
    
    // Múltiples vectores
    int count = 0;
    for (int i = 0; i < 10; ++i) {
        std::vector<uint8_t> temp(4096);
        count++;
    }
    TEST(count == 10, "Múltiples vectores creados y destruidos");
}

int main() {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║    PRUEBAS UNITARIAS - Laboratorio 1   ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    
    // Ejecutar todas las pruebas
    testPageConstruction();
    testPageWrite();
    testPageReset();
    testMultiplePages();
    testBinaryFile();
    testErrorHandling();
    testMemoryManagement();
    
    // Resumen
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║          RESUMEN DE PRUEBAS            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
    std::cout << "\nPruebas ejecutadas: " << testsRun << std::endl;
    std::cout << "Pruebas exitosas: " << testsPassed << std::endl;
    std::cout << "Pruebas fallidas: " << (testsRun - testsPassed) << std::endl;
    
    if (testsPassed == testsRun) {
        std::cout << "\n✓ TODOS LOS TESTS PASARON" << std::endl;
        return 0;
    } else {
        std::cout << "\n✗ ALGUNOS TESTS FALLARON" << std::endl;
        return 1;
    }
}
