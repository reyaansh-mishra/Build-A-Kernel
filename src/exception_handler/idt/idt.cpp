#include "idt.hpp"

extern "C" {
    void isr0();  void isr1();  void isr2();  void isr3();
    void isr4();  void isr5();  void isr6();  void isr7();
    void isr8();  void isr9();  void isr10(); void isr11();
    void isr12(); void isr13(); void isr14();
}

void idt::set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt_table[num].base_low  = (base & 0xFFFF);
    idt_table[num].base_high = (base >> 16) & 0xFFFF;
    idt_table[num].selector  = sel;
    idt_table[num].reserved  = 0;
    idt_table[num].flags     = flags; // 0x8E: Present, Ring 0, Lower bits 01110 (Interrupt gate)
}

void idt::initialize() {
    idt_pointer.limit = (sizeof(GateEntry) * 256) - 1;
    idt_pointer.base  = (uint32_t)&idt_table;

    // Map each vector to its specific assembly stub pointer
    // Parameters: Vector, ISR Address, Code Segment Selector (0x08), Flags (0x8E)
    set_gate(0,  (uint32_t)isr0,  0x08, 0x8E);
    set_gate(1,  (uint32_t)isr1,  0x08, 0x8E);
    set_gate(2,  (uint32_t)isr2,  0x08, 0x8E);
    set_gate(3,  (uint32_t)isr3,  0x08, 0x8E);
    set_gate(4,  (uint32_t)isr4,  0x08, 0x8E);
    set_gate(5,  (uint32_t)isr5,  0x08, 0x8E);
    set_gate(6,  (uint32_t)isr6,  0x08, 0x8E);
    set_gate(7,  (uint32_t)isr7,  0x08, 0x8E);
    set_gate(8,  (uint32_t)isr8,  0x08, 0x8E);
    set_gate(9,  (uint32_t)isr9,  0x08, 0x8E);
    set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    set_gate(14, (uint32_t)isr14, 0x08, 0x8E);

    // Commit to the CPU
    asm volatile("lidt (%0)" : : "r"(&idt_pointer));
}