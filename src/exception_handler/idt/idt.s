.section .text
.align 4

# Macro for exceptions that DO NOT push an error code
.macro ISR_NOERRCODE num
.global isr\num
isr\num:
    cli
    pushl $0            # Dummy error code
    pushl $\num         # Push exception number
    jmp isr_common_stub
.endm

# Macro for exceptions that DO push an error code
.macro ISR_ERRCODE num
.global isr\num
isr\num:
    cli
    # Error code is already pushed by CPU!
    pushl $\num         # Push exception number
    jmp isr_common_stub
.endm

# Generate the first 15 standard CPU exceptions
ISR_NOERRCODE 0   # Divide by zero
ISR_NOERRCODE 1   # Debug
ISR_NOERRCODE 2   # Non-maskable interrupt
ISR_NOERRCODE 3   # Breakpoint
ISR_NOERRCODE 4   # Overflow
ISR_NOERRCODE 5   # Bound range exceeded
ISR_NOERRCODE 6   # Invalid opcode
ISR_NOERRCODE 7   # Device not available
ISR_ERRCODE   8   # Double Fault
ISR_NOERRCODE 9   # Coprocessor segment overrun
ISR_ERRCODE   10  # Invalid TSS
ISR_ERRCODE   11  # Segment not present
ISR_ERRCODE   12  # Stack segment fault
ISR_ERRCODE   13  # General Protection Fault (GPF)
ISR_ERRCODE   14  # Page Fault

# --- The Common Stub ---
.extern raise_exception
isr_common_stub:

    movl $0xB8000, %edx
    movw $0x4F58, (%edx)   # 0x4F = White text on Red background, 0x58 = 'X'

    pusha               # Push EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX
    
    mov %ds, %ax
    pushl %eax          # Save current data segment descriptor
    
    # Load the flat kernel data segment (0x10)
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    pushl %esp          # Pass pointer to this register state to C++
    call raise_exception
    
    add $4, %esp        # Clean up struct pointer
    popl %eax           # Restore original data segment
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    popa                # Restore general registers
    add $8, %esp        # Clean up exception number and error code
    sti
    iret                # Return from interrupt!