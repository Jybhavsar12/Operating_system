# Building SimpleOS from Source

## Prerequisites

### Required Tools

1. **GCC Cross-Compiler** (i686-elf-gcc)
   - Required for compiling C code for x86 target
   - Standard GCC will not work as it targets your host system

2. **NASM** (Netwide Assembler)
   - Version 2.14 or higher
   - Used for assembling bootloader and kernel entry code

3. **GNU Make**
   - Build automation tool

4. **QEMU** (Optional but recommended)
   - For testing the OS without real hardware
   - qemu-system-i386 or qemu-system-x86_64

### Installing Dependencies

#### Ubuntu/Debian
```bash
sudo apt-get update
sudo apt-get install build-essential nasm qemu-system-x86
```

#### macOS
```bash
brew install nasm qemu
brew install i686-elf-gcc
```

#### Arch Linux
```bash
sudo pacman -S base-devel nasm qemu
```

### Building GCC Cross-Compiler

If your package manager does not provide i686-elf-gcc, you must build it from source:

```bash
# Set up environment
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Download binutils and gcc
wget https://ftp.gnu.org/gnu/binutils/binutils-2.39.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz

# Build binutils
tar xf binutils-2.39.tar.gz
mkdir build-binutils
cd build-binutils
../binutils-2.39/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ..

# Build gcc
tar xf gcc-12.2.0.tar.gz
mkdir build-gcc
cd build-gcc
../gcc-12.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
```

## Building the OS

### Clone the Repository

```bash
git clone https://github.com/Jybhavsar12/Operating_system.git
cd Operating_system
```

### Build Process

The build process consists of three main steps:

1. **Assemble the bootloader**
   ```bash
   nasm -f bin boot/boot.asm -o build/boot.bin
   ```

2. **Compile and assemble kernel components**
   ```bash
   nasm -f elf32 kernel/kernel_entry.asm -o build/kernel_entry.o
   i686-elf-gcc -ffreestanding -c kernel/kernel.c -o build/kernel.o
   # ... compile other C files
   ```

3. **Link kernel**
   ```bash
   i686-elf-ld -o build/kernel.bin -Ttext 0x1000 build/kernel_entry.o build/kernel.o --oformat binary
   ```

4. **Create OS image**
   ```bash
   cat build/boot.bin build/kernel.bin > build/os-image.bin
   ```

### Using Make

Simply run:
```bash
make
```

This will:
- Create the build directory
- Compile all source files
- Link the kernel
- Create the bootable OS image

### Build Targets

```bash
make all        # Build everything (default)
make bootloader # Build only the bootloader
make kernel     # Build only the kernel
make image      # Create the OS image
make clean      # Remove all build artifacts
make run        # Build and run in QEMU
make debug      # Build and run with GDB debugging
```

## Running the OS

### In QEMU

```bash
make run
```

Or manually:
```bash
qemu-system-i386 -drive format=raw,file=build/os-image.bin
```

### On Real Hardware

**WARNING**: Only do this if you know what you are doing. This can damage your system if done incorrectly.

1. Write the OS image to a USB drive:
   ```bash
   sudo dd if=build/os-image.bin of=/dev/sdX bs=512
   ```
   Replace /dev/sdX with your USB drive device.

2. Boot from the USB drive

### In VirtualBox

1. Create a new virtual machine
2. Convert the image to VDI format:
   ```bash
   VBoxManage convertfromraw build/os-image.bin build/os-image.vdi --format VDI
   ```
3. Attach the VDI as a hard disk to the VM
4. Boot the VM

## Troubleshooting

### Common Issues

**Issue**: "i686-elf-gcc: command not found"
**Solution**: Install the cross-compiler or add it to your PATH

**Issue**: "undefined reference to `__stack_chk_fail`"
**Solution**: Add `-fno-stack-protector` to GCC flags

**Issue**: Bootloader not loading kernel
**Solution**: Ensure kernel is placed immediately after bootloader in the image

**Issue**: Triple fault on boot
**Solution**: Check GDT and IDT initialization, verify stack setup

## Debugging

### Using GDB with QEMU

Terminal 1:
```bash
qemu-system-i386 -drive format=raw,file=build/os-image.bin -s -S
```

Terminal 2:
```bash
gdb
(gdb) target remote localhost:1234
(gdb) break kernel_main
(gdb) continue
```

### Debugging Tips

- Use `objdump -d build/kernel.bin` to disassemble the kernel
- Use `hexdump -C build/os-image.bin` to inspect the raw image
- Add print statements to track execution flow
- Use QEMU monitor commands for hardware inspection

