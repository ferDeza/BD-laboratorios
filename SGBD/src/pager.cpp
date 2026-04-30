#include "../include/pager.h"

Pager::Pager(const std::string& filename) {
    file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
    if (!file.is_open()) {
        // Si el archivo no existe, lo creamos
        file.open(filename, std::ios::binary | std::ios::out);
        file.close();
        file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file");
        }
    }
    file.seekg(0, std::ios::end);
    num_pages = file.tellg() / PAGE_SIZE; // Calculamos el número de páginas en el archivo
}

Pager::~Pager() {
    if (file.is_open()) {
        file.close();
    }
}

void Pager::read_page(page_id_t page_id, Page* page) {
    // Leer una página desde el disco a la memoria
    file.seekg(page_id * PAGE_SIZE, std::ios::beg);
    file.read(reinterpret_cast<char*>(page->data), PAGE_SIZE);

}

void Pager::write_page(page_id_t page_id, Page* page) {
    // Escribir una página desde la memoria al disco
    file.seekp(page_id * PAGE_SIZE, std::ios::beg);
    file.write(reinterpret_cast<const char*>(page->data), PAGE_SIZE);
    file.flush(); // Aseguramos que los datos se escriban en el disco
}
