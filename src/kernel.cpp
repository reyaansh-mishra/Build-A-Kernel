#include "../Includes/terminal.hpp"

extern "C" void kernel_initialize() {
    terminal terminal;
    terminal.initialize();
    terminal.write_string("Hello World!\n");
    terminal.write_string("New Line!\n");

    int i = 1;
    while (i < 24) {
        terminal.write_string("New Line!\n");
        i++;
    }
};