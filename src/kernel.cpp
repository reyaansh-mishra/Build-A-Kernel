#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// -----------------------------------------------------------------------------
// Forward defs:

/* Backchodi Time! VGA Colour Codes: */
enum VGA_COLOUR {
    VGA_COLOUR_BLACK = 0,
    VGA_COLOUR_BLUE = 1,
    VGA_COLOUR_GREEN = 2,
    VGA_COLOUR_CYAN = 3,
    VGA_COLOUR_RED = 4,
    VGA_COLOUR_MAGENTA = 5,
    VGA_COLOUR_BROWN = 6,
    VGA_COLOUR_LIGHT_GREY = 7,
    VGA_COLOUR_DARK_GREY = 8,
    VGA_COLOUR_LIGHT_BLUE = 9,
    VGA_COLOUR_LIGHT_GREEN = 10,
    VGA_COLOUR_LIGHT_CYAN = 11,
    VGA_COLOUR_LIGHT_RED = 12,
    VGA_COLOUR_LIGHT_MAGENTA = 13,
    VGA_COLOUR_LIGHT_BROWN = 14,
    VGA_COLOUR_WHITE = 15,
};

static inline uint8_t vga_char_colour(VGA_COLOUR fg, VGA_COLOUR bg);

// -----------------------------------------------------------------------------
// Vars and defs:

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

size_t cursor_terminal_y = 0;
size_t cursor_terminal_x = 0;
uint8_t terminal_colour;
uint16_t *terminal_buffer = (uint16_t *)VGA_MEMORY;

// -----------------------------------------------------------------------------

#if defined(__linux__)
#error "Hats Off bro! Compiling a Kernel without a Cross-Compiler! Wow."
#endif

#if !defined(__i386__)
#error                                                                                             \
    "This is a kernel for x86 (ie 32 Bit CPUs) - NOT whatever the hell you are compiling this on."
#endif

// -----------------------------------------------------------------------------

static inline uint8_t vga_char_colour(VGA_COLOUR fg, VGA_COLOUR bg) { return fg | (bg << 4); };

static inline uint16_t vga_char(unsigned char character, uint8_t colour) {
    return (uint16_t)character | ((uint16_t)colour << 8);
};

// Get size of a String (Char):
size_t get_str_length(const char *character) {
    size_t size = 0;
    while (character[size]) {
        size++;
    };

    return size;
};

// -----------------------------------------------------------------------------

void terminal_init() {

    terminal_colour = vga_char_colour(VGA_COLOUR_LIGHT_GREY, VGA_COLOUR_BLACK);

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_char(' ', terminal_colour);
        }
    };
};

void terminal_set_colour(uint8_t colour) { terminal_colour = colour; };

void terminal_put_entry(const char &character, uint8_t colour, size_t x_pos, size_t y_pos) {
    const size_t index = (y_pos * VGA_WIDTH) + x_pos;
    terminal_buffer[index] = vga_char(character, colour);
};

void terminal_put_char(const char &character) {
    terminal_put_entry(character, terminal_colour, cursor_terminal_x, cursor_terminal_y);

    if (++cursor_terminal_x == VGA_WIDTH) {
        cursor_terminal_x = 0;

        if (++cursor_terminal_y == VGA_HEIGHT) {
            cursor_terminal_y = 0;
        };
    };
};

void terminal_write(const char *data, size_t size) {
    for (size_t itr = 0; itr < size; itr++) {
        terminal_put_char(data[itr]);
    };
};

void terminal_write_str(const char *data) { terminal_write(data, get_str_length(data)); };

// -----------------------------------------------------------------------------

/* Kernel-equivalent of `int main()` */
extern "C" void kernel_start() {
    terminal_init();

    terminal_write_str("Hello World!");

    while (1) {
        asm volatile("hlt");
    }
};
