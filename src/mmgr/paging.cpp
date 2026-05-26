#include "mmgr/paging.hpp"
#include "terminal.hpp"

void mmgr::paging::setup() {

    // Explicitly clear structures to ensure unmapped regions are completely 0 (present = 0)
    for (size_t i = 0; i < 1024; i++) {
        page_directory[i] = DirectoryEntry{0};
    }

    for (size_t i = 0; i < 1024; i++) {
        page_table[i].addr      = i;
        page_table[i].present   = 1;
        page_table[i].rw        = 1;
    };

    page_directory[0].addr = (uint32_t)page_table >> 12;
    page_directory[0].present = 1;
    page_directory[0].rw = 1;

    print(sizeof(mmgr::paging::TableEntry));

    enable(); // enable() is WIP
};