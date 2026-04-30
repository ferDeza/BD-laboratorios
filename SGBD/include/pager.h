#ifndef PAGER_H
#define PAGER_H
#include "page.h"
#include "common.h"
#include <fstream>
#include <string>

class Pager{
    
    private:
    
    std::fstream file;
    uint32_t num_pages;

    public:
    Pager(const std::string& filename);
    ~Pager();

    void read_page(page_id_t page_id, Page* page);

    void write_page(page_id_t page_id, Page* page);

    uint32_t get_num_pages() const {return num_pages;};

};
#endif