# SimpleOS Architecture

## Overview

SimpleOS follows a monolithic kernel architecture with modular components. This document explains the overall system design and how different components interact.

## System Boot Process

```
Power On
    |
BIOS/UEFI
    |
Bootloader (boot.asm)
    |- Initialize hardware
    |- Load kernel from disk
    |- Switch to Protected Mode
    +- Jump to kernel
        |
Kernel Entry (kernel_entry.asm)
    |- Set up stack
    +- Call kernel_main()
        |
Kernel Main (kernel.c)
    |- Initialize GDT
    |- Initialize IDT
    |- Initialize ISR
    |- Initialize drivers
    |- Enable interrupts
    +- Enter main loop
```

## Memory Layout

### Real Mode (Bootloader)
```
0x00000000 - 0x000003FF : Interrupt Vector Table
0x00000400 - 0x000004FF : BIOS Data Area
0x00000500 - 0x00007BFF : Free memory
0x00007C00 - 0x00007DFF : Bootloader (512 bytes)
0x00007E00 - 0x0009FFFF : Free memory
0x000A0000 - 0x000FFFFF : Video memory, ROM
```

### Protected Mode (Kernel)
```
0x00000000 - 0x00000FFF : Reserved
0x00001000 - 0x0000FFFF : Kernel code and data
0x00010000 - 0x???????? : Heap (dynamic allocation)
0x000B8000 - 0x000B8FA0 : VGA text buffer
```

## Component Architecture

### 1. Bootloader Layer

File: boot/boot.asm

Responsibilities:
- Initialize CPU in 16-bit real mode
- Load kernel sectors from disk into memory at 0x1000
- Set up GDT for protected mode
- Switch CPU to 32-bit protected mode
- Transfer control to kernel entry point

Key Functions:
- load_kernel: Reads 15 sectors from disk using BIOS INT 0x13
- switch_to_pm: Transitions from real mode to protected mode

### 2. Kernel Layer

#### Kernel Entry
File: kernel/kernel_entry.asm

Responsibilities:
- Entry point for kernel execution
- Calls C kernel main function

#### Kernel Core
File: kernel/kernel.c

Responsibilities:
- Initialize all subsystems in correct order
- Coordinate between components
- Main kernel loop with HLT instruction

### 3. CPU Management

#### Global Descriptor Table (GDT)
Files: kernel/cpu/gdt.c, kernel/cpu/gdt_flush.asm

Purpose: Defines memory segments for protected mode

Segments:
- Null segment (required by x86 architecture)
- Code segment: base=0, limit=4GB, ring 0
- Data segment: base=0, limit=4GB, ring 0

#### Interrupt Descriptor Table (IDT)
Files: kernel/cpu/idt.c, kernel/cpu/idt_flush.asm

Purpose: Maps interrupt numbers to handler functions

Contains 256 entries:
- 0-31: CPU exceptions
- 32-47: Hardware interrupts (IRQs)
- 48-255: Available for software interrupts

#### Interrupt Service Routines (ISR)
Files: kernel/cpu/isr.c, kernel/cpu/isr_asm.asm

Purpose: Handle CPU exceptions and hardware interrupts

Features:
- PIC remapping (IRQ 0-15 mapped to interrupts 32-47)
- Exception handling with error messages
- IRQ dispatching to device drivers
- Proper EOI (End of Interrupt) signaling

### 4. Drivers

#### Screen Driver
File: kernel/drivers/screen.c

Purpose: VGA text mode output (80x25 characters)

Memory: 0xB8000 (VGA text buffer)

Features:
- Character and string printing
- Automatic scrolling when screen is full
- Cursor management via VGA controller ports
- Color support (16 foreground, 8 background colors)

Key Functions:
- print(): Print null-terminated string
- print_char(): Print single character
- clear_screen(): Clear entire display
- set_cursor(): Update cursor position

#### Keyboard Driver
File: kernel/drivers/keyboard.c

Purpose: Handle keyboard input via PS/2 controller

Hardware: IRQ1 (interrupt 33)

Features:
- Scancode to ASCII conversion
- Shift key support
- Real-time character echo to screen

#### Port I/O Driver
File: kernel/drivers/ports.c

Purpose: Low-level hardware port communication

Functions:
- port_byte_in/out: 8-bit I/O operations
- port_word_in/out: 16-bit I/O operations

### 5. Memory Management

File: kernel/memory/memory.c

Purpose: Manage dynamic memory allocation

Features:
- Simple bump allocator starting at 0x10000
- Page-aligned allocation support
- Utility functions (memcpy, memset, strlen, strcmp)

Functions:
- kmalloc(): Allocate kernel memory
- kmalloc_aligned(): Allocate page-aligned memory
- kfree(): Free memory (placeholder)

## Data Flow Examples

### Example 1: User Types a Key

```
1. User presses key on keyboard
2. Keyboard controller sends scancode to port 0x60
3. Keyboard controller triggers IRQ1
4. PIC forwards interrupt to CPU
5. CPU looks up interrupt 33 in IDT
6. CPU calls irq1 handler (isr_asm.asm)
7. Handler saves registers and calls irq_handler()
8. irq_handler() dispatches to keyboard_handler()
9. keyboard_handler() reads scancode from port 0x60
10. Scancode converted to ASCII character
11. Character passed to print_char()
12. print_char() writes to VGA buffer at 0xB8000
13. Character appears on screen
14. Handler sends EOI to PIC
15. Registers restored, execution returns
```

### Example 2: Printing to Screen

```
1. Code calls print("Hello")
2. print() iterates through string characters
3. For each character, print_char() is called
4. print_char() gets current cursor position
5. Calculates VGA buffer offset: (row * 80 + col) * 2
6. Writes character to 0xB8000 + offset
7. Writes color attribute to 0xB8000 + offset + 1
8. Increments cursor position
9. Checks if scrolling is needed
10. Updates hardware cursor via ports 0x3D4/0x3D5
```

## Design Principles

1. Simplicity: Code is straightforward and easy to understand
2. Modularity: Each component has a clear, single responsibility
3. Documentation: Every function is well-commented
4. Educational: Code prioritizes clarity over optimization
5. Extensibility: Easy to add new features and drivers

## Future Enhancements

- Process scheduling and multitasking
- Virtual memory with paging
- File system (FAT12/16 or custom)
- User mode and system calls
- Additional device drivers (timer, disk, etc.)
- Network stack
- Graphics mode support

## References

- Intel 64 and IA-32 Architectures Software Developer Manuals
- OSDev Wiki: https://wiki.osdev.org/
- The Little Book About OS Development

