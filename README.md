# SimpleOS - Educational Operating System

## Overview

SimpleOS is a lightweight, educational operating system designed to help students and enthusiasts understand the fundamentals of OS development. Built from scratch using C and x86 Assembly, this project demonstrates core operating system concepts in a clear and accessible way.

## Project Goals

- Educational: Learn OS development fundamentals through hands-on implementation
- Lightweight: Minimal footprint with essential features only
- Well-Documented: Extensive comments and documentation for every component
- Modular: Clean architecture that is easy to understand and extend

## Features

- Custom bootloader (16-bit real mode)
- 32-bit protected mode kernel
- VGA text mode display driver
- Global Descriptor Table (GDT)
- Interrupt Descriptor Table (IDT)
- Keyboard driver with interrupt handling
- Basic memory management
- Simple command-line shell

## Architecture

```
SimpleOS Architecture
├── Bootloader (boot.asm)
│   ├── BIOS initialization
│   ├── Load kernel into memory
│   └── Switch to protected mode
│
├── Kernel (kernel/)
│   ├── Entry point (kernel_entry.asm)
│   ├── Main kernel (kernel.c)
│   ├── Drivers
│   │   ├── Screen driver (screen.c)
│   │   └── Keyboard driver (keyboard.c)
│   ├── CPU
│   │   ├── GDT (gdt.c)
│   │   ├── IDT (idt.c)
│   │   └── ISR (isr.c)
│   └── Memory
│       └── Memory manager (memory.c)
│
└── Shell (shell.c)
    └── Command interpreter
```

## Quick Start

### Prerequisites

- GCC Cross-Compiler (i686-elf-gcc)
- NASM (Netwide Assembler)
- Make
- QEMU (for testing)
- Linux/macOS (or WSL on Windows)

### Installation

1. Clone the repository
   ```bash
   git clone https://github.com/Jybhavsar12/Operating_system.git
   cd Operating_system
   ```

2. Install dependencies (Ubuntu/Debian)
   ```bash
   sudo apt-get update
   sudo apt-get install build-essential nasm qemu-system-x86
   ```

3. Build the OS
   ```bash
   make
   ```

4. Run in QEMU
   ```bash
   make run
   ```

5. Clean build files
   ```bash
   make clean
   ```

## Documentation

Detailed documentation is available in the `docs/` directory:

- [Building from Source](docs/BUILDING.md)
- [Architecture Overview](docs/ARCHITECTURE.md)
- [Bootloader Explained](docs/BOOTLOADER.md)
- [Kernel Development](docs/KERNEL.md)
- [Memory Management](docs/MEMORY.md)
- [Driver Development](docs/DRIVERS.md)
- [Contributing Guide](docs/CONTRIBUTING.md)

## Development

### Project Structure

```
Operating_system/
├── boot/               # Bootloader code
│   └── boot.asm       # 16-bit bootloader
├── kernel/            # Kernel source code
│   ├── kernel.c       # Main kernel
│   ├── kernel_entry.asm
│   ├── drivers/       # Device drivers
│   ├── cpu/           # CPU-related code
│   └── memory/        # Memory management
├── include/           # Header files
├── docs/              # Documentation
├── build/             # Build output
├── Makefile           # Build system
└── README.md          # This file
```

### Building Components

```bash
# Build only the bootloader
make bootloader

# Build only the kernel
make kernel

# Create bootable image
make image
```

## Testing

Run the OS in QEMU emulator:

```bash
# Standard run
make run

# Run with debugging
make debug

# Run with serial output
make run-serial
```

## Learning Resources

- [OSDev Wiki](https://wiki.osdev.org/)
- [Writing a Simple Operating System from Scratch](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [The Little Book About OS Development](https://littleosbook.github.io/)
- [Intel x86 Architecture Manual](https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-manual-325462.html)

## Contributing

Contributions are welcome! Please read [CONTRIBUTING.md](docs/CONTRIBUTING.md) for details on our code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

Jyot Bhavsar
- GitHub: [@Jybhavsar12](https://github.com/Jybhavsar12)

## Acknowledgments

- OSDev community for excellent documentation
- All contributors and supporters of this educational project
- Inspired by classic operating systems like MINIX and Linux
