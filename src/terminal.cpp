#include "../Includes/terminal.hpp"
#include "../Includes/vga.hpp"

size_t inline string_length(const char *string) {
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

    // if (terminal::row >= vga::HEIGHT) {
    //     terminal::row = 0;
    //     terminal::column = 0;
    // }

    if (character == '\n') {
        terminal::column = 0;
        terminal::row += 1;
        return;
    };

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

void terminal::write_string(const char *string) { terminal::write(string, string_length(string)); };

void terminal::scroll_buffer_down() {
    write_buffer[1] = nullptr;

    for (size_t i = 0; i < vga::HEIGHT - 1; i++) {
        write_buffer[i] = write_buffer[i + 1];
    }
    write_buffer[vga::HEIGHT - 1] = nullptr;
};

void print(const char *string, uint8_t sel_colour) {

    terminal::set_colour(sel_colour);

    if (terminal::row >= vga::HEIGHT - 1) {
        // re-render whole buffer
        terminal::initialize();

        terminal::scroll_buffer_down();
        for (terminal::iterator = 0; terminal::iterator < vga::HEIGHT; terminal::iterator++) {
            if (terminal::write_buffer[terminal::iterator]) {
                terminal::write_string(terminal::write_buffer[terminal::iterator]);
                terminal::write_string("\n");
            }
        }
    };

    terminal::write_buffer[terminal::row] = string;
    terminal::write_string(string);
    terminal::write_string("\n");

    terminal::set_colour(vga::VGA_COLOUR_WHITE);
};