#include "../Includes/terminal.hpp"
#include "mmgr/paging.hpp"

extern "C" void kernel_initialize() {
    terminal::initialize();
    print("Hello World!", vga::VGA_COLOUR_RED);

    mmgr::paging::setup();


    // Paging Test - Keeping for the heck of it  
    // Volatile prevents the compiler from optimizing this away.
    // We are trying to write to 0x00500000 (5MB), which is NOT mapped!
    // volatile uint32_t* broken_pointer = (uint32_t*)0x00500000;
    // *broken_pointer = 0xDEADBEEF;
};