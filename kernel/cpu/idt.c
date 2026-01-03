/**
 * idt.c - Interrupt Descriptor Table implementation
 * Sets up interrupt handling for the CPU
 */

#include "../../include/idt.h"
#include "../../include/types.h"

// IDT entry structure
struct idt_entry {
    uint16_t base_low;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

// IDT pointer structure
struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// IDT with 256 entries
struct idt_entry idt[256];
struct idt_ptr idtp;

// External assembly function to load IDT
extern void idt_flush(uint32_t);

/**
 * idt_set_gate - Set an IDT entry
 * @num: Interrupt number
 * @base: Address of interrupt handler
 * @selector: Code segment selector
 * @flags: Flags (present, privilege level, gate type)
 */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    
    idt[num].selector = selector;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

/**
 * idt_init - Initialize the Interrupt Descriptor Table
 */
void idt_init(void) {
    idtp.limit = (sizeof(struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;
    
    // Clear IDT
    int i;
    for (i = 0; i < 256; i++) {
        idt_set_gate(i, 0, 0, 0);
    }
    
    // Load the IDT
    idt_flush((uint32_t)&idtp);
}

