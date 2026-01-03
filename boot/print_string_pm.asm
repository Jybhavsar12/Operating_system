; print_string_pm - Print a null-terminated string in 32-bit protected mode
; Input: EBX = address of null-terminated string
; Writes directly to VGA text buffer at 0xB8000

[bits 32]

VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

print_string_pm:
    pusha
    mov edx, VIDEO_MEMORY       ; Start of video memory

.loop:
    mov al, [ebx]               ; Load character from EBX
    mov ah, WHITE_ON_BLACK      ; Set attribute byte

    cmp al, 0                   ; Check for null terminator
    je .done

    mov [edx], ax               ; Write character and attribute to video memory
    add ebx, 1                  ; Move to next character
    add edx, 2                  ; Move to next video memory position (char + attribute)

    jmp .loop

.done:
    popa
    ret

