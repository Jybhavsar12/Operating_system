; Kernel Entry Point
; This is the first code that runs when the kernel is loaded
; It sets up the environment and calls the C kernel

[bits 32]                       ; We're in 32-bit protected mode
[extern kernel_main]            ; Declare external C function

call kernel_main                ; Call C kernel main function

jmp $                           ; Hang if kernel returns

