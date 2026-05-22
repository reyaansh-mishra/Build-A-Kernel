/* Constants for Multi-Boot Headers */
.set ALIGN,     1<<0
.set MEMINFO,    1<<1
.set FLAGS,     ALIGN | MEMINFO
.set MAGIC,     0x1BADB002
.set CHECKSUM,  -(MAGIC + FLAGS)

/*  Declare a multiboot header that marks the program as a kernel */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Create THE STACK */
.section .bss
.align 16
stack_bottom:
    .skip 16384 # 16 Kib
stack_top:
    
/* the `_start` entry - where code execution begins. */
.section .text
.global _start
.type _start, @function
_start:

	/* DISABLE INTERRUPTS ASAP */
	cli

    /* NOTICE! 32Bit */
    /* Setup the stack */
    mov $stack_top, %esp

    /* Good place to init Processors and all before the high-level Cpp kernel starts up */

    call kernel_start

    /* If the system has nothing more to do, put the computer into an
	infinite loop. To do that:
	1) Disable interrupts with cli (clear interrupt enable in eflags).
	   They are already disabled by the bootloader, so this is not needed.
	   Mind that you might later enable interrupts and return from
	   kernel_main (which is sort of nonsensical to do).
	2) Wait for the next interrupt to arrive with hlt (halt instruction).
	   Since they are disabled, this will lock up the computer.
	3) Jump to the hlt instruction if it ever wakes up due to a
	   non-maskable interrupt occurring or due to system management mode. */
	cli
1:	hlt
	jmp 1b

/* Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing. */

.size _start, . - _start