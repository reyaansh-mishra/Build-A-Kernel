#include "../Includes/terminal.hpp"

size_t inline terminal::string_length(const char *string) {
    size_t length = 0;
    while (string[length]) {
        length++;
    }

    return length;
};

void terminal::initialize() {
    terminal::row = 0;
    terminal::column = 0;
    terminal::colour = vga::entry_color(vga::VGA_COLOUR_LIGHT_GREY, vga::VGA_COLOUR_BLACK);

    for (size_t y = 0; y < vga::HEIGHT; y++) {
        for (size_t x = 0; x < vga::WIDTH; x++) {
            const size_t index = (y * vga::WIDTH) + x;
            buffer[index] = vga::entry(' ', colour);
        };
    };
};

void terminal::set_colour(uint8_t colour) { terminal::colour = colour; };

void terminal::put_entry(char character, uint8_t colour, size_t x, size_t y) {
    const size_t index = (y * vga::WIDTH) + x;
    buffer[index] = vga::entry(character, colour);
};

void terminal::put_char(char character) {
    put_entry(character, terminal::colour, terminal::column, terminal::row);

    if (++terminal::column == vga::WIDTH) {
        terminal::column = 0;

        if (++terminal::row == vga::HEIGHT) {
            terminal::row = 0;
        };
    };
};

void terminal::write(const char *string, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal::put_char(string[i]);
    };
};

void terminal::write_string(const char *string) {
    terminal::write(string, terminal::string_length(string));
};