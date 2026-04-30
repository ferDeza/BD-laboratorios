#include "../include/page.h"
#include <cstring>

Page::Page() {
    reset();
}
void Page::reset() {
    std::memset(data, 0, PAGE_SIZE); // Limpiamos el buffer de la página
    PageHeader* header = get_header();
    header->page_id = 0; // Asignamos un ID de página por defecto
    header->num_slots = 0; // Inicializamos el número de slots a 0
    header->free_space_ptr = sizeof(PageHeader); // El espacio libre comienza después del header
}



PageHeader* Page::get_header() {
    return reinterpret_cast<PageHeader*>(data); // El header estA al inicio de la pAgina
}

Slot* Page::get_slot_array() {
    return reinterpret_cast<Slot*>(data + sizeof(PageHeader)); // El array de slots comienza despues del header
}

int Page::insert_record(const uint8_t* record, uint16_t record_size) {
    
    PageHeader* header = get_header();
    Slot* slots = get_slot_array();

    // Vemos si hay espacio suficiente para el nuevo registro
    if (header->free_space_ptr + record_size > PAGE_SIZE) {
        return -1; // No hay espacio suficiente
    }

    // Insertamos el registro en la pagina
    std::memcpy(data + header->free_space_ptr, record, record_size);

    // Actualizamos el slot correspondiente
    slots[header->num_slots].offset = header->free_space_ptr;
    slots[header->num_slots].size = record_size;

    // Actualizamos el header
    header->free_space_ptr += record_size;
    return header->num_slots++; // Incrementamos el número de slots y devolvemos el slot_id
}

int Page::get_record(slot_id_t slot_id) {
    PageHeader* header = get_header();
    Slot* slots = get_slot_array();

    if (slot_id >= header->num_slots) {
        return -1; // Slot ID inválido
    }

    return slots[slot_id].offset; // Devolvemos el offset del registro
}