#include "idt.hpp"
#include "terminal.hpp"

idt::GateEntry idt::idt_table[256] __attribute__((aligned(16)));
idt::Pointer idt::idt_pointer;

extern "C" {
    void isr0();  void isr1();  void isr2();  void isr3();
    void isr4();  void isr5();  void isr6();  void isr7();
    void isr8();  void isr9();  void isr10(); void isr11();
    void isr12(); void isr13(); void isr14();
}

void idt::set_entry(uint8_t pos, uint32_t base, uint16_t sel, uint8_t flags) {
    idt::idt_table[pos].address_low     = base & 0xFFFF;    /* Mask off the lower 16 bits */
    idt::idt_table[pos].address_high    = base >> 16;
    idt::idt_table[pos].code_segment    = sel;
    idt::idt_table[pos].flags           = flags;
};

void idt::initialize() {

    idt_pointer.size = (sizeof(idt_table) - 1);
    idt_pointer.addr = (uint32_t)&idt_table;

    set_entry(0, (uint32_t)isr0, 0x10, 0x8E);
    set_entry(1, (uint32_t)isr1, 0x10, 0x8E);
    set_entry(2, (uint32_t)isr2, 0x10, 0x8E);
    set_entry(3, (uint32_t)isr3, 0x10, 0x8E);
    set_entry(4, (uint32_t)isr4, 0x10, 0x8E);
    set_entry(5, (uint32_t)isr5, 0x10, 0x8E);
    set_entry(6, (uint32_t)isr6, 0x10, 0x8E);
    set_entry(7, (uint32_t)isr7, 0x10, 0x8E);
    set_entry(8, (uint32_t)isr8, 0x10, 0x8E);
    set_entry(9, (uint32_t)isr9, 0x10, 0x8E);
    set_entry(10, (uint32_t)isr10, 0x10, 0x8E);
    set_entry(11, (uint32_t)isr11, 0x10, 0x8E);
    set_entry(12, (uint32_t)isr12, 0x10, 0x8E);
    set_entry(13, (uint32_t)isr13, 0x10, 0x8E);
    set_entry(14, (uint32_t)isr14, 0x10, 0x8E);

    asm volatile("lidt (%0)" : : "r"(&idt_pointer));

    print("IDT Initialized!\n", vga::VGA_COLOUR_LIGHT_GREY);
};