#include "mmgr.hpp"

namespace mmgr::paging {

  // Vars
  struct DirectoryEntry {
    uint32_t present            : 1;
    uint32_t rw                 : 1;
    uint32_t user_accessible    : 1;
    uint32_t write_through      : 1;
    uint32_t cache_status       : 1;
    uint32_t accessed           : 1;  // CPU sets this when accessed
    uint32_t reserved           : 1;
    uint32_t page_size          : 1;
    uint32_t ignored            : 4;
    uint32_t addr               : 20;
  };

  struct TableEntry {
    uint32_t present            : 1;
    uint32_t rw                 : 1;
    uint32_t user_accessible    : 1;
    uint32_t write_through      : 1;
    uint32_t cache_status       : 1;
    uint32_t accessed           : 1;  // CPU sets this when accessed
    uint32_t dirty              : 1;  // CPU sets this when WRITTEN to
    uint32_t reserved           : 1;
    uint32_t global             : 1;  // keep in TLB across CR3 switches
    uint32_t ignored            : 3;
    uint32_t addr               : 20;

  };

  inline DirectoryEntry page_directory[1024] __attribute__((aligned(4096)));
  inline TableEntry page_table[1024] __attribute__((aligned(4096)));


  // ----------------------------------------
  // Function Defs

  void setup();
    __attribute__((always_inline)) inline void enable()  {

      // Identity map the first 4MB
      // Crucial: The physical address must equal the virtual address for now!

      asm volatile(
          "mov %0, %%cr3\n"
          "mov %%cr0, %%eax\n"
          "or $0x80000000, %%eax\n"
          "mov %%eax, %%cr0\n"
          :
          : "r"(page_directory)
          : "eax"
      );
  }; // the actual CR3 + CR0 asm

  // ----------------------------------------
  // Static Asserts
  static_assert(sizeof(DirectoryEntry) == 4, "DirectoryEntry must be 4 bytes");
  static_assert(sizeof(TableEntry) == 4, "TableEntry must be 4 bytes");

}