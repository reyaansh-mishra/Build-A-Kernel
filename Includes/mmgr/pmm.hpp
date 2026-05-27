#include "mmgr/mmgr.hpp"

namespace mmgr::pmm {
    void init();

    uint32_t alloc();     // 1 << pos for alloc
    int dealloc(uint32_t addr);  // 0 << pos for dealloc
}