/* Declare Constants for Multiboot Header - THESE ARE VARIABLES RN */
.set ALIGN,     1<<0        /* Align loaded modules on Page Header */
.set MEMINFO,   1<<1        /* Provide Memory Map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,     0x1BADB002  /* The "Magic Number" which informs that we are MULTIBOOT-CAPABLE */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */


/* Declare the Actual Multiboot Harder */
.section    .multiboot
    .align  4           /* Align to 16 bytes - 4 byte boundary */
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

/* Zero bss and Define Stack */
.section    .bss
    .align 16
    stack_bottom:
        .skip 16384 /* 16 KiB */
    stack_top:

/* Actual Enty point */
.section .text
    .global _start
    .type _start, @function

    _start:
        /* Setup Stack */
        mov $stack_top, %esp

        /* Good place to do other bullshit */
        call kernel_initialize

        /* Put system on Infinite Loop */
        cli
        1: hlt
        jmp 1b

/* Set the size of the _start symbol to the current location '.' minus its start.
Useful when debugging */

.size _start, . - _start
