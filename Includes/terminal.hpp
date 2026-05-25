#pragma once

#include "vga.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

namespace terminal {

    inline uint8_t colour;
    volatile inline uint16_t *buffer = reinterpret_cast<uint16_t *>(0xB8000);
    inline size_t row;
    inline size_t column;
    inline const char *write_buffer[vga::HEIGHT];
    inline size_t iterator = 0;

    void set_colour(uint8_t colour);
    void put_entry(char character, uint8_t colour, size_t x, size_t y);
    void put_char(char character);
    void write(const char *string, size_t size);

    void write_string(const char *string);
    void initialize();
    void scroll_buffer_down();

}; // namespace terminal

void print(const char *string, uint8_t sel_colour = vga::VGA_COLOUR_WHITE);
size_t inline string_length(const char *string);
