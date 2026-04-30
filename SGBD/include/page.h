#ifndef PAGE_H
#define PAGE_H

#include <cstdint>
#include "common.h"
#include <vector>

class Page{


    public:
        //buffer de memoria para la página
        uint8_t data[PAGE_SIZE];
    
        Page();         
    
        void reset();
        //insert un registro en la página, devuelve el slot_id o -1 si no hay espacio
        int insert_record(const uint8_t* record, uint16_t record_size);
    
        //puntero a los datos de un slot
        int get_record(slot_id_t slot_id);
    
        PageHeader* get_header();
        Slot* get_slot_array(); 


};
#endif