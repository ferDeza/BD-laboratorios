#ifndef COMMON_H
#define COMMON_H


#include <cstdint>

const uint32_t PAGE_SIZE = 4096;
typedef uint32_t page_id_t;
typedef uint16_t slot_id_t;


struct Slot{
    uint16_t offset;
    uint16_t size;

};


struct PageHeader{

    page_id_t page_id;
    uint16_t num_slots;
    uint16_t free_space_ptr;

};

#endif