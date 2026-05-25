#include "../Includes/terminal.hpp"

extern "C" void kernel_initialize() {
    terminal::initialize();
    terminal::write_string("Hello World!\n");
};