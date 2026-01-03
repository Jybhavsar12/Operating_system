; switch_to_pm - Switch from 16-bit real mode to 32-bit protected mode

[bits 16]

switch_to_pm:
    cli                         ; Disable interrupts

    lgdt [gdt_descriptor]       ; Load GDT descriptor

    ; Set PE (Protection Enable) bit in CR0
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    ; Far jump to flush CPU pipeline and enter 32-bit mode
    jmp CODE_SEG:init_pm

[bits 32]

init_pm:
    ; Update segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Set up stack
    mov ebp, 0x90000
    mov esp, ebp

    ; Jump to protected mode entry point
    call BEGIN_PM

