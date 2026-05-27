.section .text

.macro ISR_NOERRCODE code
.global isr\code
isr\code:
    cli
    pushl $0
    pushl $\code
    jmp isr_common_stub
.endm

# --------------------------------------------------------

.macro ISR_ERRCODE code
.global isr\code
isr\code:
    cli
    pushl $\code
    jmp isr_common_stub
.endm

ISR_NOERRCODE   0
ISR_NOERRCODE   1
ISR_NOERRCODE   2
ISR_NOERRCODE   3
ISR_NOERRCODE   4
ISR_NOERRCODE   5
ISR_NOERRCODE   6
ISR_NOERRCODE   7
ISR_NOERRCODE   9

ISR_ERRCODE     8
ISR_ERRCODE     10
ISR_ERRCODE     11
ISR_ERRCODE     12
ISR_ERRCODE     13
ISR_ERRCODE     14


# --------------------------------------------------------------------------------------------

.extern raise_exception

isr_common_stub:
    pusha
    push %ds

    mov $0x10, %ax

    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    pushl %esp

    call raise_exception

    add $4, %esp

    popl %eax

    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa

    add $8, %esp 

    iret