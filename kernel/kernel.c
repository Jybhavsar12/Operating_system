/**
 * SimpleOS Kernel
 * Main kernel entry point and initialization
 */

#include "../include/screen.h"
#include "../include/types.h"
#include "../include/gdt.h"
#include "../include/idt.h"
#include "../include/isr.h"
#include "../include/keyboard.h"

/**
 * kernel_main - Main kernel entry point
 *
 * This function is called by kernel_entry.asm after the bootloader
 * has loaded the kernel and switched to protected mode.
 */
void kernel_main(void) {
    // Clear the screen
    clear_screen();

    // Print welcome message
    print("SimpleOS Kernel Loaded Successfully\n");
    print("Version 0.1.0 - Educational Operating System\n");
    print("Copyright (c) 2026 Jyot Bhavsar\n\n");

    // Initialize system components
    print("Initializing GDT...\n");
    gdt_init();

    print("Initializing IDT...\n");
    idt_init();

    print("Initializing ISR...\n");
    isr_init();

    print("Initializing keyboard...\n");
    keyboard_init();

    print("\nKernel initialized in 32-bit protected mode\n");
    print("All systems operational.\n\n");
    print("Type to test keyboard input:\n");
    print("> ");

    // Kernel main loop
    while(1) {
        // Halt CPU until next interrupt
        __asm__ __volatile__("hlt");
    }
}

