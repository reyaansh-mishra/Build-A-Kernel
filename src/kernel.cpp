#include "../Includes/terminal.hpp"
#include "mmgr/paging.hpp"
#include "interrupt_handler/idt.hpp"
#include "mmgr/pmm.hpp"

extern "C" void kernel_initialize() {
    terminal::initialize();
    mmgr::paging::setup();
    idt::initialize();
    mmgr::pmm::init();


    print("Hello World!\n", vga::VGA_COLOUR_RED);

    uint32_t page =  mmgr::pmm::alloc();
    print(page);
    print(mmgr::pmm::dealloc(page));

    // Paging & Kernel Panic Test - Keeping for the heck of it  
    // Volatile prevents the compiler from optimizing this away.
    // We are trying to write to 0x00500000 (5MB), which is NOT mapped!
    // volatile uint32_t* broken_pointer = (uint32_t*)0x00500000;
    // *broken_pointer = 0xDEADBEEF;
};