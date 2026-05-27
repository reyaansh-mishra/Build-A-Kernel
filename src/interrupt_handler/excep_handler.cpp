#include "exception_handler.hpp"
#include "terminal.hpp"

extern "C" void raise_exception(uint32_t esp) {

    terminal::initialize();

    const char* seperator = "\n\n===============================================================================\n";

    excep_handler::registers* regs = reinterpret_cast<excep_handler::registers*>(esp); 

    print("\n!!!! YOU HAVE FUCKED UP REALLY BAD !!!!\n\n", vga::VGA_COLOUR_RED);    

    print("Exception Number: "); print(regs->int_no); print("                       ");
    print("Error Code: "); print(regs->err_code);

    print(seperator);

    print("It Crashed Here: "); print_hex(regs->eip); print("\n");

    if (regs->int_no == 14) {    
        uint32_t cr2;
        asm volatile("mov %%cr2, %0" : "=r"(cr2));
        print("CR2: "); print_hex(cr2);
    };

    print(seperator);
    print("System Registers:\n");
    
    print("EAX: "); print_hex(regs->eax); print("    ");
    print("EBX: "); print_hex(regs->ebx); print("    ");
    print("ECX: "); print_hex(regs->ecx); print("    ");
    print("EDX: "); print_hex(regs->edx); print("\n");
    print("ESI: "); print_hex(regs->esi); print("    ");
    print("EDI: "); print_hex(regs->edi); print("\n");
    print("EBP: "); print_hex(regs->ebp); print("    ");
    print("ESP: "); print_hex(regs->esp);

    print(seperator);
    print("Segments:\n");

    print("CS:"); print_hex(regs->cs); print("\n");
    print("DS:"); print_hex(regs->ds);

    print(seperator);
    print("EFLAGS: ");
    print(regs->eflags);

    while (1);
};