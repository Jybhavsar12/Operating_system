; disk_load - Load sectors from disk using BIOS interrupt
; Input:
;   DH = number of sectors to read
;   DL = drive number
;   BX = memory address to load sectors to

[bits 16]

disk_load:
    pusha                       ; Save all registers
    push dx

    ; Reset disk system first
    mov ah, 0x00                ; BIOS reset disk function
    int 0x13                    ; Call BIOS
    jc .disk_error              ; If reset fails, error

    pop dx
    push dx

    ; Now read sectors
    mov ah, 0x02                ; BIOS read sector function
    mov al, dh                  ; Number of sectors to read
    mov cl, 0x02                ; Start reading from sector 2 (after boot sector)
    mov ch, 0x00                ; Cylinder 0
    mov dh, 0x00                ; Head 0
    ; DL already contains drive number
    ; BX already contains buffer address

    int 0x13                    ; Call BIOS disk read
    jc .disk_error              ; Jump if error (carry flag set)

    pop dx
    cmp al, dh                  ; Check if we read the right number of sectors
    jne .sectors_error          ; If not, error

    popa                        ; Restore all registers
    ret

.disk_error:
    mov bx, DISK_ERROR_MSG
    call print_string
    jmp $                       ; Hang forever

.sectors_error:
    mov bx, SECTORS_ERROR_MSG
    call print_string
    jmp $                       ; Hang forever

DISK_ERROR_MSG db "Disk read error!", 0x0D, 0x0A, 0
SECTORS_ERROR_MSG db "Wrong number of sectors read!", 0x0D, 0x0A, 0

