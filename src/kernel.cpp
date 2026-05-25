#include "../Includes/terminal.hpp"

extern "C" void kernel_initialize() {
    terminal::initialize();
    print("Hello World!", vga::VGA_COLOUR_RED);
    print("New Line!");

    print("HELP MEE");
    print("HELP MEE YES");
    print("HELP MEE YES No");
    print("HELP MEE YES No NO");
    print("HELP MEE YES No NO Yes");
    print("HELP MEE YES No NO Yes YAAY");
    print("HELP MEE YES No NO Yes YAAY NAY");
    print("HELP MEE YES No NO Yes YAAY NAY 1");
};