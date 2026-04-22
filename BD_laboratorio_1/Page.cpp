#include "Page.h"
#include <iostream>

// Constructor
Page::Page(page_id_t id) : pageId(id) {
    // Inicializar el vector con PAGE_SIZE bytes en cero
    data.resize(PAGE_SIZE, 0);
}

// Escribir datos en la página
void Page::writeData(const void* src, size_t offset, size_t len) {
    // Verificar que offset + len no exceda el tamaño de la página
    if (offset + len > PAGE_SIZE) {
        std::cerr << "Error: intento de escribir fuera de los limites de la pagina" << std::endl;
        return;
    }

    if (src == nullptr) {
        std::cerr << "Error: puntero de origen es nulo" << std::endl;
        return;
    }

    // Copiar datos desde src a data
    std::memcpy(data.data() + offset, src, len);
}

// Leer datos de la página
void Page::readData(void* dest, size_t offset, size_t len) const {
    // Verificar que offset + len no exceda el tamaño de la página
    if (offset + len > PAGE_SIZE) {
        std::cerr << "Error: intento de leer fuera de los límites de la página" << std::endl;
        return;
    }

    if (dest == nullptr) {
        std::cerr << "Error: puntero de destino es nulo" << std::endl;
        return;
    }

    // Copiar datos desde data a dest
    std::memcpy(dest, data.data() + offset, len);
}

// Obtener el ID de la página
page_id_t Page::getPageId() const {
    return pageId;
}

// Limpiar la página (llenar con ceros)
void Page::reset() {
    std::fill(data.begin(), data.end(), 0);
}

// Obtener el tamaño de la página
size_t Page::getSize() const {
    return PAGE_SIZE;
}
