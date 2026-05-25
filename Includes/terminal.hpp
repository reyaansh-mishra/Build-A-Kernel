#pragma once

#include "vga.hpp"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

class terminal {

  private:
    size_t row;
    size_t column;
    uint8_t colour;
    uint16_t *buffer = reinterpret_cast<uint16_t *>(0xB8000);

    size_t inline string_length(const char *string);
    void set_colour(uint8_t colour);
    void put_entry(char character, uint8_t colour, size_t x, size_t y);
    void put_char(char character);
    void write(const char *string, size_t size);

  public:
    void write_string(const char *string);
    void initialize();
    char write_buffer[vga::HEIGHT][vga::WIDTH];

}; // namespace terminal

void print(const char *string);