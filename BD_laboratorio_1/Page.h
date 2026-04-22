#ifndef PAGE_H
#define PAGE_H

#include <vector>
#include <cstdint>
#include <cstring>

const size_t PAGE_SIZE = 4096;  // 4 KB
const uint32_t INVALID_PAGE_ID = 0xFFFFFFFF;

typedef uint32_t page_id_t;

class Page {
private:
    std::vector<uint8_t> data;  // 4096 bytes
    page_id_t pageId;

public:
    // Constructor
    Page(page_id_t id = INVALID_PAGE_ID);

    // Escribir datos en la página
    // src: puntero a los datos a escribir
    // offset: posición inicial en la página
    // len: cantidad de bytes a escribir
    void writeData(const void* src, size_t offset, size_t len);

    // Leer datos de la página
    // dest: puntero donde guardar los datos leídos
    // offset: posición inicial en la página
    // len: cantidad de bytes a leer
    void readData(void* dest, size_t offset, size_t len) const;

    // Obtener el ID de la página
    page_id_t getPageId() const;

    // Limpiar la página (llenar con ceros)
    void reset();

    // Obtener el tamaño de la página
    size_t getSize() const;
};

#endif // PAGE_H
