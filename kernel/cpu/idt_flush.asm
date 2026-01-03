; idt_flush - Load the IDT
; Called from idt.c

[global idt_flush]

idt_flush:
    mov eax, [esp + 4]      ; Get pointer to IDT descriptor
    lidt [eax]              ; Load IDT
    ret

