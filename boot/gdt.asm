; Global Descriptor Table (GDT) for protected mode
; Defines memory segments for code and data

[bits 16]

gdt_start:

; Null descriptor (required)
gdt_null:
    dd 0x0                      ; 4 bytes of zeros
    dd 0x0                      ; 4 bytes of zeros

; Code segment descriptor
gdt_code:
    dw 0xffff                   ; Limit (bits 0-15)
    dw 0x0                      ; Base (bits 0-15)
    db 0x0                      ; Base (bits 16-23)
    db 10011010b                ; Access byte: present, ring 0, code, executable, readable
    db 11001111b                ; Flags and limit (bits 16-19): 4KB granularity, 32-bit
    db 0x0                      ; Base (bits 24-31)

; Data segment descriptor
gdt_data:
    dw 0xffff                   ; Limit (bits 0-15)
    dw 0x0                      ; Base (bits 0-15)
    db 0x0                      ; Base (bits 16-23)
    db 10010010b                ; Access byte: present, ring 0, data, writable
    db 11001111b                ; Flags and limit (bits 16-19): 4KB granularity, 32-bit
    db 0x0                      ; Base (bits 24-31)

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1  ; Size of GDT (16-bit)
    dd gdt_start                ; Address of GDT (32-bit)

; Segment selector offsets
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

