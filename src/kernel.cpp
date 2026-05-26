#include "../Includes/terminal.hpp"
#include "mmgr/paging.hpp"
#include "idt.hpp"

extern "C" void kernel_initialize() {
    terminal::initialize();
    mmgr::paging::setup();
    // idt::initialize();

    print("Hello World!", vga::VGA_COLOUR_RED);



    // Paging & Kernel Panic Test - Keeping for the heck of it  
    // Volatile prevents the compiler from optimizing this away.
    // We are trying to write to 0x00500000 (5MB), which is NOT mapped!
    volatile uint32_t* broken_pointer = (uint32_t*)0x00300000;
    *broken_pointer = 0xDEADBEEF;
};