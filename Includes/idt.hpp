#include <stdint.h>

namespace idt {
    struct GateEntry {
        uint16_t base_low;        // The lower 16 bits of the ISR function address
        uint16_t selector;        // Kernel Code Segment selector (usually 0x08)
        uint8_t  reserved   = 0;  // Always 0
        uint8_t  flags;           // Type and attributes (usually 0x8E for 32-bit interrupt gate)
        uint16_t base_high;       // The upper 16 bits of the ISR function address
    } __attribute__((packed));    // CRITICAL: Prevent clang from padding this

    struct Pointer {
        uint16_t limit;           // Size of IDT array minus 1
        uint32_t base;            // Linear address of the first element in our array
    } __attribute__((packed));

    // Define the table of 256 interrupts
    inline GateEntry idt_table[256] __attribute__((aligned(16)));
    inline Pointer idt_pointer;

    // Functions
    void set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
    void initialize();
}