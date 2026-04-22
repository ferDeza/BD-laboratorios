#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

const size_t PAGE_SIZE = 4096; // 4 KB

int main() {
    std::cout << "=== PARTE 1: MANEJO DE ARCHIVOS BINARIOS ===" << std::endl;
    std::cout << std::endl;

    // Crear archivo y escribir 10 páginas de 4 KB
    std::string filename = "data.db";
    std::ofstream file(filename, std::ios::binary);

    if (!file) {
        std::cerr << "Error al crear el archivo" << std::endl;
        return 1;
    }

    std::cout << "Creando archivo: " << filename << std::endl;
    std::cout << "Tamanio de pagina: " << PAGE_SIZE << " bytes (4 KB)" << std::endl;
    std::cout << std::endl;

    // Escribir 10 páginas
    for (int pageNum = 0; pageNum < 10; pageNum++) {
        std::vector<uint8_t> page(PAGE_SIZE);
        
        // Llenar cada página con su número de página
        for (size_t i = 0; i < PAGE_SIZE; i++) {
            page[i] = pageNum % 256; // Número de página (mod 256 para caber en uint8_t)
        }

        file.write(reinterpret_cast<const char*>(page.data()), PAGE_SIZE);
        std::cout << "PAgina " << pageNum << " escrita: " << PAGE_SIZE << " bytes" << std::endl;
    }

    file.close();
    std::cout << std::endl;

    // Leer y verificar el archivo
    std::ifstream readFile(filename, std::ios::binary);
    if (!readFile) {
        std::cerr << "Error al abrir el archivo para lectura" << std::endl;
        return 1;
    }

    // Obtener tamaño del archivo
    readFile.seekg(0, std::ios::end);
    size_t fileSize = readFile.tellg();
    readFile.seekg(0, std::ios::beg);

    int numPages = fileSize / PAGE_SIZE;
    std::cout << "Tamanio total del archivo: " << fileSize << " bytes" << std::endl;
    std::cout << "Numero de páginas: " << numPages << std::endl;
    std::cout << std::endl;

    // Leer algunas páginas para verificar
    std::cout << "Verificando contenido de paginas:" << std::endl;
    for (int i = 0; i < numPages; i++) {
        std::vector<uint8_t> buffer(PAGE_SIZE);
        readFile.read(reinterpret_cast<char*>(buffer.data()), PAGE_SIZE);
        
        std::cout << "Pagina " << i << ": primer byte = " 
                  << (int)buffer[0] << ", ultimo byte = " 
                  << (int)buffer[PAGE_SIZE - 1] << std::endl;
    }

    readFile.close();
    std::cout << std::endl;
    std::cout << "Archivo creado exitosamente!" << std::endl;

    return 0;
}
