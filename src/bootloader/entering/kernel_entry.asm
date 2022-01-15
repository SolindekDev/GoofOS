global _start;
[bits 32]

_start:
    [extern KERNEL_ENTRY] 
    call KERNEL_ENTRY
    jmp $