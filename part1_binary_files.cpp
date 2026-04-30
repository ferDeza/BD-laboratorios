#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

const size_t PAGE_SIZE = 4096;  // 4 KB
const int NUM_PAGES = 10;       // 10 páginas

/**
 * PARTE 1: MANEJO DE ARCHIVOS BINARIOS
 * 
 * OBJETIVO: Crear un archivo binario "data.db" y escribir 10 páginas de 4 KB
 * cada una con un patrón conocido (número de página)
 * 
 * DICCIONARIO DE FUNCIONES Y COMANDOS:
 * 
 * 1. std::ofstream - Abre archivo en modo escritura binaria
 *    - Modo: std::ios::binary para escritura binaria
 * 
 * 2. write(const char* s, streamsize n) - Escribe n bytes al archivo
 *    - Parámetro 1: Puntero a buffer
 *    - Parámetro 2: Número de bytes a escribir
 * 
 * 3. seekp(pos_type pos) - Posiciona el puntero de escritura
 *    - Permite ubicar la posición exacta en el archivo
 * 
 * 4. tellp() - Obtiene la posición actual del puntero de escritura
 *    - Útil para verificar ubicación en el archivo
 * 
 * 5. std::ifstream - Abre archivo en modo lectura binaria
 *    - Modo: std::ios::binary para lectura binaria
 * 
 * 6. read(char* s, streamsize n) - Lee n bytes del archivo
 *    - Parámetro 1: Puntero a buffer destino
 *    - Parámetro 2: Número de bytes a leer
 * 
 * 7. seekg(pos_type pos) - Posiciona el puntero de lectura
 *    - Permite ubicar la posición exacta para lectura
 * 
 * 8. tellg() - Obtiene la posición actual del puntero de lectura
 *    - Útil para determinar posición en el archivo
 * 
 * 9. gcount() - Retorna el número de bytes leídos en la última operación
 *    - Permite verificar cuántos bytes fueron realmente leídos
 */

void createBinaryFile() {
    std::cout << "\n=== PARTE 1: MANEJO DE ARCHIVOS BINARIOS ===" << std::endl;
    std::cout << "Creando archivo binario 'data.db'..." << std::endl;
    
    // Abrir archivo en modo escritura binaria
    std::ofstream outFile("data.db", std::ios::binary);
    
    if (!outFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo data.db" << std::endl;
        return;
    }
    
    // Escribir 10 páginas de 4 KB cada una
    for (int pageNum = 0; pageNum < NUM_PAGES; ++pageNum) {
        // Crear un buffer de 4 KB
        std::vector<uint8_t> page(PAGE_SIZE);
        
        // Llenar la página con un patrón: número de página
        for (size_t i = 0; i < PAGE_SIZE; ++i) {
            // Usar el número de página como patrón (módulo 256 para que capa en uint8_t)
            page[i] = static_cast<uint8_t>(pageNum % 256);
        }
        
        // Escribir la página en el archivo
        outFile.write(reinterpret_cast<const char*>(page.data()), PAGE_SIZE);
        
        std::cout << "Página " << pageNum << " escrita. Posición: " 
                  << outFile.tellp() << " bytes" << std::endl;
    }
    
    outFile.close();
    std::cout << "\nArchivo 'data.db' creado exitosamente." << std::endl;
    std::cout << "Tamaño total: " << (NUM_PAGES * PAGE_SIZE) << " bytes\n" << std::endl;
}

void readBinaryFile() {
    std::cout << "=== LECTURA Y VERIFICACIÓN ===" << std::endl;
    
    // Abrir archivo en modo lectura binaria
    std::ifstream inFile("data.db", std::ios::binary);
    
    if (!inFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo data.db para lectura" << std::endl;
        return;
    }
    
    // Leer y verificar cada página
    for (int pageNum = 0; pageNum < NUM_PAGES; ++pageNum) {
        std::vector<uint8_t> page(PAGE_SIZE);
        
        // Posicionar el puntero de lectura
        inFile.seekg(pageNum * PAGE_SIZE);
        
        // Leer la página
        inFile.read(reinterpret_cast<char*>(page.data()), PAGE_SIZE);
        
        size_t bytesRead = inFile.gcount();
        
        // Verificar que la página contiene el patrón esperado
        bool patternCorrect = true;
        for (size_t i = 0; i < bytesRead; ++i) {
            if (page[i] != static_cast<uint8_t>(pageNum % 256)) {
                patternCorrect = false;
                break;
            }
        }
        
        std::cout << "Página " << pageNum << " leída. Bytes: " << bytesRead 
                  << ", Patrón correcto: " << (patternCorrect ? "SÍ" : "NO") << std::endl;
    }
    
    inFile.close();
    std::cout << "\nVerificación completada.\n" << std::endl;
}

int main_part1() {
    createBinaryFile();
    readBinaryFile();
    return 0;
}
