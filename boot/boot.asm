; SimpleOS Bootloader
; This bootloader loads the kernel from disk and switches to 32-bit protected mode

[org 0x7c00]                    ; BIOS loads bootloader at address 0x7C00
[bits 16]                       ; Start in 16-bit real mode

KERNEL_OFFSET equ 0x1000        ; Memory offset where kernel will be loaded

    mov [BOOT_DRIVE], dl        ; BIOS stores boot drive in DL, save it

    ; Set up stack
    mov bp, 0x9000              ; Set stack base pointer
    mov sp, bp                  ; Set stack pointer

    ; Print boot message
    mov bx, MSG_REAL_MODE
    call print_string

    ; Load kernel from disk
    call load_kernel

    ; Switch to protected mode
    call switch_to_pm

    jmp $                       ; Should never reach here

; Include files
%include "boot/print_string.asm"
%include "boot/disk_load.asm"
%include "boot/gdt.asm"
%include "boot/print_string_pm.asm"
%include "boot/switch_to_pm.asm"

[bits 16]
; Load kernel from disk into memory
load_kernel:
    mov bx, MSG_LOAD_KERNEL
    call print_string

    mov bx, KERNEL_OFFSET       ; Load kernel to this address
    mov dh, 25                  ; Load 25 sectors (12.5KB, enough for kernel)
    mov dl, [BOOT_DRIVE]        ; Drive number
    call disk_load

    ret

[bits 32]
; Entry point after switching to protected mode
BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_string_pm

    ; Jump to kernel
    call KERNEL_OFFSET

    ; If kernel returns, hang
    jmp $

; Data
BOOT_DRIVE      db 0
MSG_REAL_MODE   db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE   db "Successfully switched to 32-bit Protected Mode", 0
MSG_LOAD_KERNEL db "Loading kernel into memory", 0

; Boot sector padding and magic number
times 510-($-$$) db 0           ; Pad with zeros
dw 0xaa55                       ; Boot signature

