#ifndef PAGE_H
#define PAGE_H

#include <vector>
#include <cstdint>
#include <cstring>

// Constantes para el manejo de páginas
constexpr size_t PAGE_SIZE = 4096;  // Tamaño de página: 4 KB
typedef uint32_t page_id_t;
constexpr page_id_t INVALID_PAGE_ID = 0xFFFFFFFF;

/**
 * Clase Page - Representa una página de 4KB en memoria
 * 
 * Funcionalidades:
 * - Almacenamiento de datos de 4096 bytes
 * - Lectura y escritura en posiciones específicas
 * - Identificación única mediante page_id
 * - Limpieza/reset de datos
 */
class Page {
private:
    std::vector<uint8_t> data;      // Buffer de 4096 bytes
    page_id_t pageId;               // Identificador único de la página

public:
    /**
     * Constructor de la clase Page
     * @param id Identificador de la página (por defecto INVALID_PAGE_ID)
     */
    Page(page_id_t id = INVALID_PAGE_ID);

    /**
     * Escribe datos en la página en una posición específica
     * @param src Puntero a los datos a escribir
     * @param offset Posición de inicio en la página
     * @param len Número de bytes a escribir
     */
    void writeData(const void* src, size_t offset, size_t len);

    /**
     * Lee datos de la página desde una posición específica
     * @param dest Puntero donde almacenar los datos leídos
     * @param offset Posición de inicio en la página
     * @param len Número de bytes a leer
     */
    void readData(void* dest, size_t offset, size_t len) const;

    /**
     * Obtiene el identificador de la página
     * @return ID de la página
     */
    page_id_t getPageId() const;

    /**
     * Limpia todos los datos de la página (rellena con ceros)
     */
    void reset();

    /**
     * Obtiene el tamaño de la página
     * @return Tamaño en bytes (4096)
     */
    size_t getSize() const;
};

#endif // PAGE_H
