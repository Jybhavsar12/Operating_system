; gdt_flush - Load the GDT and update segment registers
; Called from gdt.c

[global gdt_flush]
[extern gp]

gdt_flush:
    mov eax, [esp + 4]      ; Get pointer to GDT descriptor
    lgdt [eax]              ; Load GDT
    
    mov ax, 0x10            ; 0x10 is offset to data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    
    jmp 0x08:.flush         ; 0x08 is offset to code segment
.flush:
    ret

