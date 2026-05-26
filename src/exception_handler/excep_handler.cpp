#include "exception_handler.hpp"
#include "terminal.hpp"
#include <stdint.h>

extern "C" void raise_exception(uint32_t esp) {
        // We cast the stack pointer back to our structural register state
        struct CpuRegisters {
            uint32_t ds;
            uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
            uint32_t int_no, err_code;
            uint32_t eip, cs, eflags;
        } *regs = (CpuRegisters*)esp;

        // Print the pure details to your serial / VGA log!
        print("\n!!! KERNEL PANIC !!!\n");
        print("Caught Exception: "); print(regs->int_no);
        print(" | Error Code: ");    print(regs->err_code);
        print("\nFailed at EIP: ");  print_hex(regs->eip);
        
        if (regs->int_no == 14) {
            uint32_t cr2;
            asm volatile("mov %%cr2, %0" : "=r"(cr2));
            print("\nFaulting Memory Address: "); print_hex(cr2);
        }

        while(1); // Halt completely
}