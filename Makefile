# SimpleOS Makefile
# Build system for the operating system

# Compiler and tools
CC = i686-elf-gcc
LD = i686-elf-ld
ASM = nasm

# Directories
BUILD_DIR = build
KERNEL_DIR = kernel
BOOT_DIR = boot
INCLUDE_DIR = include

# Compiler flags
CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -Wall -Wextra -I$(INCLUDE_DIR)
LDFLAGS = -m elf_i386 -Ttext 0x1000 --oformat binary
ASMFLAGS = -f elf32

# Source files
C_SOURCES = $(wildcard $(KERNEL_DIR)/*.c) \
            $(wildcard $(KERNEL_DIR)/drivers/*.c) \
            $(wildcard $(KERNEL_DIR)/cpu/*.c) \
            $(wildcard $(KERNEL_DIR)/memory/*.c)

ASM_SOURCES = $(wildcard $(KERNEL_DIR)/*.asm) \
              $(wildcard $(KERNEL_DIR)/cpu/*.asm)

# Object files
C_OBJECTS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))
ASM_OBJECTS = $(patsubst %.asm, $(BUILD_DIR)/%.o, $(ASM_SOURCES))

# Output files
BOOTLOADER = $(BUILD_DIR)/boot.bin
KERNEL = $(BUILD_DIR)/kernel.bin
OS_IMAGE = $(BUILD_DIR)/os-image.bin

# Default target
all: $(OS_IMAGE)

# Create OS image by concatenating bootloader and kernel
$(OS_IMAGE): $(BOOTLOADER) $(KERNEL)
	@echo "Creating OS image..."
	cat $(BOOTLOADER) $(KERNEL) > $(OS_IMAGE)
	@echo "Build complete: $(OS_IMAGE)"

# Build bootloader
$(BOOTLOADER): $(BOOT_DIR)/boot.asm | $(BUILD_DIR)
	@echo "Assembling bootloader..."
	$(ASM) -f bin $< -o $@

# Build kernel
$(KERNEL): $(BUILD_DIR)/$(KERNEL_DIR)/kernel_entry.o $(C_OBJECTS) $(ASM_OBJECTS)
	@echo "Linking kernel..."
	$(LD) $(LDFLAGS) -o $@ $^

# Compile C source files
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble kernel assembly files
$(BUILD_DIR)/%.o: %.asm | $(BUILD_DIR)
	@mkdir -p $(dir $@)
	@echo "Assembling $<..."
	$(ASM) $(ASMFLAGS) $< -o $@

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Run in QEMU
run: $(OS_IMAGE)
	@echo "Starting QEMU..."
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE)

# Run with debugging
debug: $(OS_IMAGE)
	@echo "Starting QEMU with GDB server..."
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE) -s -S

# Run with serial output
run-serial: $(OS_IMAGE)
	@echo "Starting QEMU with serial output..."
	qemu-system-i386 -drive format=raw,file=$(OS_IMAGE) -serial stdio

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	rm -rf $(BUILD_DIR)

# Build only bootloader
bootloader: $(BOOTLOADER)

# Build only kernel
kernel: $(KERNEL)

# Phony targets
.PHONY: all run debug run-serial clean bootloader kernel

# Help target
help:
	@echo "SimpleOS Build System"
	@echo ""
	@echo "Targets:"
	@echo "  all         - Build the complete OS image (default)"
	@echo "  bootloader  - Build only the bootloader"
	@echo "  kernel      - Build only the kernel"
	@echo "  run         - Build and run in QEMU"
	@echo "  debug       - Build and run with GDB debugging"
	@echo "  run-serial  - Build and run with serial output"
	@echo "  clean       - Remove all build artifacts"
	@echo "  help        - Show this help message"

