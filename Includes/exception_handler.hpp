#include "global_includes.hpp"

namespace exception_handler {
    struct registers {
        uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by 'pusha'
        uint32_t int_no, err_code;                       // Pushed manually
        uint32_t eip, cs, eflags, useresp, ss;           // Pushed automatically by CPU
    };

    extern "C" void exception(registers regist);
}