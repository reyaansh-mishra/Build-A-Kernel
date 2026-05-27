#include "global_includes.hpp"

namespace excep_handler {
    struct registers {
        uint32_t ds;
        uint32_t edi,esi,ebp,esp,ebx,edx,ecx,eax;
        uint32_t int_no, err_code;
        uint32_t eip, cs, eflags;
    };
}

extern "C" void raise_exception(uint32_t esp);
