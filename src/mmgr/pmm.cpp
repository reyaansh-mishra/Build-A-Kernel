#include "mmgr/pmm.hpp"

static uint8_t mem_bitmap[131072];
static uint32_t max_pages = 1048576;
extern uint32_t kernel_mem_end;

static void mark(uint32_t page, bool used) {
    if (used)
        mem_bitmap[page / 8] |= (1 << (page % 8));
    else
        mem_bitmap[page / 8] &= ~(1 << (page % 8));
}

static bool check(uint32_t page) {  return (mem_bitmap[page / 8] & (1 << (page % 8)));  };  /* 1 -> Page Used; 0 -> Page Free */

void mmgr::pmm::init() {
    for (size_t i = 0; i < sizeof(mem_bitmap); i++) {  mem_bitmap[i] = 0;  };   // Simple Reset Script for "Just-In-Case" Senarios

    for (uint32_t current_page = 0; current_page < (uint32_t)&kernel_mem_end/4096; current_page++) {
        mark(current_page, 1);
    };

    return;
};


uint32_t mmgr::pmm::alloc() {
    for (uint32_t target_page = (uint32_t)&kernel_mem_end/4096; target_page < max_pages; target_page++) {
        if (!(check(target_page))) {
            mark(target_page, 1);
            return target_page * 4096;
        };
    };

    return 0;
};


int mmgr::pmm::dealloc(uint32_t addr) {
    if (check(addr/4096)) {
        mark(addr/4096, 0);
        return 1;
    }

    return 0;
};