; print_string - Print a null-terminated string in 16-bit real mode
; Input: BX = address of null-terminated string
; Uses BIOS interrupt 0x10

[bits 16]

print_string:
    pusha                       ; Save all registers
    mov ah, 0x0e                ; BIOS teletype output

.loop:
    mov al, [bx]                ; Load character from BX
    cmp al, 0                   ; Check for null terminator
    je .done                    ; If null, we're done

    int 0x10                    ; Print character in AL

    inc bx                      ; Move to next character
    jmp .loop                   ; Repeat

.done:
    ; Print newline
    mov al, 0x0d                ; Carriage return
    int 0x10
    mov al, 0x0a                ; Line feed
    int 0x10

    popa                        ; Restore all registers
    ret

