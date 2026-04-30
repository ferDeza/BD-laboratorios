
#include <iostream>
#include "common.h"
#include "page.h"
#include "pager.h"


using namespace std;

int main() {
    
    const string db_file = "data.db";
    {
        std::cout << "--- Fase de Escritura ---" << std::endl;
        Pager my_pager(db_file);
        Page my_page;

        // Creamos un registro de prueba (un string convertido a bytes)
        std::string record1 = "Primer registro del SGBD";
        std::string record2 = "Datos de prueba numero dos";

        // Insertamos en la página
        int slot1 = my_page.insert_record(reinterpret_cast<const uint8_t*>(record1.c_str()), record1.size());
        int slot2 = my_page.insert_record(reinterpret_cast<const uint8_t*>(record2.c_str()), record2.size());

        if (slot1 != -1 && slot2 != -1) {
            std::cout << "Registros insertados en slots: " << slot1 << " y " << slot2 << std::endl;
            
            // Guardamos la página en la posicion 0 del archivo
            my_pager.write_page(0, &my_page);
            std::cout << "Pagina 0 guardada en disco." << std::endl;
        }
    } // Aquí el objeto my_pager se destruye y el archivo se cierra

    std::cout << "\n---------------------------\n" << std::endl;

    // --- FASE 2: LECTURA Y VERIFICACIÓN ---
    {
        std::cout << "--- Fase de Lectura ---" << std::endl;
        Pager my_pager(db_file);
        Page read_page;

        // Leemos la página que guardamos antes
        my_pager.read_page(0, &read_page);
        
        PageHeader* hdr = read_page.get_header();
        Slot* slots = read_page.get_slot_array();

        std::cout << "Paginas en archivo: " << my_pager.get_num_pages() << std::endl;
        std::cout << "Registros encontrados en la pagina: " << hdr->num_slots << std::endl;

        // Recuperamos los datos usando los slots
        for (int i = 0; i < hdr->num_slots; ++i) {
            uint16_t offset = slots[i].offset;
            uint16_t size = slots[i].size;
            
            std::string recovered_data(reinterpret_cast<char*>(&read_page.data[offset]), size);
            std::cout << "Slot " << i << ": " << recovered_data << std::endl;
        }
    }
    return 0;   
}