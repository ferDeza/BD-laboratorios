#include "Page.h"
#include <iostream>
#include <stdexcept>

/**
 * IMPLEMENTACIÓN DE CLASE PAGE
 * 
 * Diccionario de Funciones:
 * - Page(page_id_t): Constructor que inicializa un buffer de 4096 bytes
 * - writeData(): Escribe datos en posición específica usando memcpy
 * - readData(): Lee datos desde posición específica usando memcpy
 * - getPageId(): Retorna el ID de la página
 * - reset(): Llena el buffer con ceros usando memset
 * - getSize(): Retorna el tamaño constante de la página (4096)
 */

Page::Page(page_id_t id) : pageId(id) {
    // Inicializar el vector con PAGE_SIZE bytes, todos en cero
    data.resize(PAGE_SIZE, 0);
}

void Page::writeData(const void* src, size_t offset, size_t len) {
    if (src == nullptr) {
        throw std::invalid_argument("Puntero de origen no válido");
    }
    if (offset + len > PAGE_SIZE) {
        throw std::out_of_range("Intento de escribir fuera de los límites de la página");
    }
    
    // Copiar datos desde src al vector data
    std::memcpy(data.data() + offset, src, len);
}

void Page::readData(void* dest, size_t offset, size_t len) const {
    if (dest == nullptr) {
        throw std::invalid_argument("Puntero de destino no válido");
    }
    if (offset + len > PAGE_SIZE) {
        throw std::out_of_range("Intento de leer fuera de los límites de la página");
    }
    
    // Copiar datos desde el vector data al destino
    std::memcpy(dest, data.data() + offset, len);
}

page_id_t Page::getPageId() const {
    return pageId;
}

void Page::reset() {
    // Llenar todos los bytes de la página con ceros
    std::fill(data.begin(), data.end(), 0);
}

size_t Page::getSize() const {
    return PAGE_SIZE;
}
