#pragma once

#include "vga.hpp"

namespace terminal {
    inline size_t row;
    inline size_t column;
    inline uint8_t colour;
    inline uint16_t *buffer = reinterpret_cast<uint16_t *>(0xB8000);

    size_t inline string_length(const char *string);
    void initialize();
    void set_colour(uint8_t colour);
    void put_entry(char character, uint8_t colour, size_t x, size_t y);
    void put_char(char character);
    void write(const char *string, size_t size);
    void write_string(const char *string);

} // namespace terminal