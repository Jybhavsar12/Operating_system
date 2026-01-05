# SimpleOS Documentation

Welcome to the SimpleOS documentation! This directory contains comprehensive documentation about the operating system's architecture, components, and usage.

## Documentation Index

### 📘 Core Documentation

#### [SYSTEM_OVERVIEW.md](SYSTEM_OVERVIEW.md)
Complete system overview including:
- System architecture and component hierarchy
- Boot process (BIOS → Bootloader → Kernel)
- Memory layout and organization
- Interrupt system (IDT, ISR, IRQ)
- Device drivers (VGA, Keyboard, Ports)
- Technical specifications

**Start here** if you want to understand how the entire system works.

---

#### [KEYBOARD_INPUT.md](KEYBOARD_INPUT.md)
Detailed documentation of the keyboard input system:
- PS/2 keyboard driver implementation
- Scancode to ASCII conversion
- Interrupt handling flow (IRQ1)
- Shift key support
- Shell input processing

**Read this** to understand how keyboard input is processed from hardware to shell.

---

#### [FILE_SYSTEM.md](FILE_SYSTEM.md)
In-memory file system documentation:
- File structure and storage
- File system operations (create, read, write, delete, list)
- Implementation details
- Limitations and constraints
- Usage examples

**Read this** to understand how files are stored and managed in memory.

---

#### [SHELL_COMMANDS.md](SHELL_COMMANDS.md)
Complete shell command reference:
- System commands (help, clear, about, echo)
- File system commands (touch, write, cat, ls, rm)
- Command syntax and examples
- Command parsing and execution flow

**Read this** for a complete reference of all available shell commands.

---

## Quick Start

### For Users
1. Read [SHELL_COMMANDS.md](SHELL_COMMANDS.md) to learn available commands
2. Try the example usage sessions in [FILE_SYSTEM.md](FILE_SYSTEM.md)

### For Developers
1. Start with [SYSTEM_OVERVIEW.md](SYSTEM_OVERVIEW.md) for architecture overview
2. Read [KEYBOARD_INPUT.md](KEYBOARD_INPUT.md) to understand interrupt-driven I/O
3. Study [FILE_SYSTEM.md](FILE_SYSTEM.md) for data structure design
4. Review source code in conjunction with documentation

## System Architecture Diagram

```
┌─────────────────────────────────────────────────────────┐
│                    User Interface                        │
│              (Shell - Command Interpreter)               │
│                   kernel/shell.c                         │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│                  System Services                         │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │  File System │  │    Memory    │  │    String    │  │
│  │   (In-RAM)   │  │  Management  │  │  Utilities   │  │
│  │ filesystem.c │  │   memory.c   │  │   kernel.c   │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│                  Device Drivers                          │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │   Keyboard   │  │  VGA Screen  │  │     Ports    │  │
│  │   (PS/2)     │  │  (Text Mode) │  │   (I/O)      │  │
│  │ keyboard.c   │  │   screen.c   │  │   ports.c    │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│              Hardware Abstraction Layer                  │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐  │
│  │     GDT      │  │     IDT      │  │   ISR/IRQ    │  │
│  │  (Segments)  │  │ (Interrupts) │  │  (Handlers)  │  │
│  │    gdt.c     │  │    idt.c     │  │    isr.c     │  │
│  └──────────────┘  └──────────────┘  └──────────────┘  │
└─────────────────────────────────────────────────────────┘
                          ↓
┌─────────────────────────────────────────────────────────┐
│                   Hardware (x86 CPU)                     │
└─────────────────────────────────────────────────────────┘
```

## Key Concepts

### Boot Process
1. **BIOS** loads bootloader to 0x7C00
2. **Bootloader** loads kernel to 0x1000 and switches to protected mode
3. **Kernel** initializes hardware and enters main loop

### Interrupt-Driven I/O
- CPU halts (`hlt`) until interrupt occurs
- Keyboard press triggers IRQ1 (interrupt 33)
- Handler processes input and returns to main loop

### Memory Management
- Flat memory model (no paging)
- GDT provides basic segmentation
- Stack at 0x9000, kernel at 0x1000
- VGA buffer at 0xB8000

### File System
- In-memory storage (non-persistent)
- Simple array-based structure
- 16 files maximum, 512 bytes each

## File Organization

```
docs/
├── README.md              # This file
├── SYSTEM_OVERVIEW.md     # Complete system documentation
├── KEYBOARD_INPUT.md      # Keyboard driver documentation
├── FILE_SYSTEM.md         # File system documentation
└── SHELL_COMMANDS.md      # Command reference
```

## Contributing to Documentation

When adding new features to SimpleOS, please update the relevant documentation:

1. Update [SYSTEM_OVERVIEW.md](SYSTEM_OVERVIEW.md) for architectural changes
2. Update [SHELL_COMMANDS.md](SHELL_COMMANDS.md) for new commands
3. Create new documentation files for major new subsystems
4. Keep diagrams up-to-date with code changes

## Additional Resources

- **Source Code**: `../kernel/`, `../boot/`
- **Build System**: `../Makefile`
- **OSDev Wiki**: https://wiki.osdev.org/
- **Intel Manuals**: https://www.intel.com/sdm

---

**SimpleOS** - A minimal educational operating system  
Version 0.2.0

