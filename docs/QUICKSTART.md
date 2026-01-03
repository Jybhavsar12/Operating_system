# SimpleOS Quick Start Guide

## Introduction

This guide will help you get SimpleOS up and running quickly.

## Prerequisites

Before building SimpleOS, ensure you have the following installed:

- i686-elf-gcc (cross-compiler for x86)
- NASM (Netwide Assembler)
- GNU Make
- QEMU (for testing)

## Quick Build and Run

### Step 1: Clone the Repository

```bash
git clone https://github.com/Jybhavsar12/Operating_system.git
cd Operating_system
```

### Step 2: Build the OS

```bash
make
```

This will:
- Assemble the bootloader
- Compile all C source files
- Assemble all kernel assembly files
- Link the kernel
- Create the bootable OS image

### Step 3: Run in QEMU

```bash
make run
```

This will launch QEMU and boot SimpleOS.

## Using SimpleOS

Once SimpleOS boots, you will see:

```
SimpleOS Kernel Loaded Successfully
Version 0.1.0 - Educational Operating System
Copyright (c) 2026 Jyot Bhavsar

Initializing GDT...
Initializing IDT...
Initializing ISR...
Initializing keyboard...
Initializing shell...

Kernel initialized in 32-bit protected mode
All systems operational.

Welcome to SimpleOS! Type 'help' for available commands.
>
```

### Available Commands

- **help** - Display list of available commands
- **clear** - Clear the screen
- **about** - Display system information
- **echo [text]** - Echo text back to the screen

### Example Session

```
> help

Available commands:
  help    - Display this help message
  clear   - Clear the screen
  about   - Display system information
  echo    - Echo text back to screen

> about

SimpleOS v0.1.0
Educational Operating System
Copyright (c) 2026 Jyot Bhavsar

Features:
  - 32-bit protected mode
  - VGA text mode driver
  - Keyboard input support
  - Interrupt handling (GDT, IDT, ISR)
  - Basic memory management

> echo Hello, World!
Hello, World!

> clear
[screen clears]

>
```

## Troubleshooting

### Build Errors

**Error: i686-elf-gcc: command not found**

Solution: Install the i686-elf cross-compiler. See docs/BUILDING.md for instructions.

**Error: nasm: command not found**

Solution: Install NASM:
```bash
# Ubuntu/Debian
sudo apt-get install nasm

# macOS
brew install nasm
```

### Runtime Issues

**QEMU doesn't start**

Solution: Install QEMU:
```bash
# Ubuntu/Debian
sudo apt-get install qemu-system-x86

# macOS
brew install qemu
```

**Keyboard not working**

Solution: Click inside the QEMU window to capture keyboard input.

**Screen is blank**

Solution: This is normal if the bootloader or kernel failed to load. Check build output for errors.

## Next Steps

- Read docs/ARCHITECTURE.md to understand the system design
- Read docs/BUILDING.md for detailed build instructions
- Explore the source code in kernel/ and boot/ directories
- Try modifying the shell to add new commands
- Experiment with adding new features

## Development Workflow

### Making Changes

1. Edit source files
2. Run `make clean` to remove old build artifacts
3. Run `make` to rebuild
4. Run `make run` to test

### Debugging

To debug with GDB:

Terminal 1:
```bash
make debug
```

Terminal 2:
```bash
gdb
(gdb) target remote localhost:1234
(gdb) break kernel_main
(gdb) continue
```

## Additional Resources

- OSDev Wiki: https://wiki.osdev.org/
- Intel x86 Manual: https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html
- NASM Documentation: https://www.nasm.us/docs.php

## Getting Help

If you encounter issues:

1. Check the documentation in docs/
2. Review the source code comments
3. Search the OSDev wiki
4. Open an issue on GitHub

## Contributing

Contributions are welcome! Please read docs/CONTRIBUTING.md for guidelines.

