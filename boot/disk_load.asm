; disk_load - Load sectors from disk using BIOS interrupt
; Input:
;   DH = number of sectors to read
;   DL = drive number
;   BX = memory address to load sectors to

[bits 16]

disk_load:
    push dx                     ; Save DX (number of sectors)

    mov ah, 0x02                ; BIOS read sector function
    mov al, dh                  ; Number of sectors to read
    mov ch, 0x00                ; Cylinder 0
    mov dh, 0x00                ; Head 0
    mov cl, 0x02                ; Start from sector 2 (sector 1 is bootloader)

    int 0x13                    ; BIOS disk interrupt

    jc .disk_error              ; Jump if carry flag set (error)

    pop dx                      ; Restore DX
    cmp al, dh                  ; AL = sectors actually read
    jne .disk_error             ; If not equal, error occurred
    ret

.disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $                       ; Hang

DISK_ERROR_MSG db "Disk read error!", 0

