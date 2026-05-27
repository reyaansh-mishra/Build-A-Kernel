#include "global_includes.hpp"

namespace idt {
    struct GateEntry {
        uint16_t address_low;
        uint16_t code_segment;
        uint8_t reserved = 0;
        uint8_t flags;
        uint16_t address_high;

    } __attribute__((packed));

    struct Pointer {
        uint16_t size;
        uint32_t addr;
    } __attribute__((packed));

    extern GateEntry idt_table[256];
    extern Pointer idt_pointer;
    // Functions
    void initialize();
    void set_entry(uint8_t pos, uint32_t base, uint16_t sel, uint8_t flags);
};