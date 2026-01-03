/**
 * gdt.c - Global Descriptor Table implementation
 * Sets up memory segmentation for protected mode
 */

#include "../../include/gdt.h"

// GDT entry structure
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

// GDT pointer structure
struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// GDT with 3 entries: null, code, data
struct gdt_entry gdt[3];
struct gdt_ptr gp;

// External assembly function to load GDT
extern void gdt_flush(uint32_t);

/**
 * gdt_set_gate - Set a GDT entry
 * @num: Entry number
 * @base: Base address
 * @limit: Segment limit
 * @access: Access flags
 * @gran: Granularity flags
 */
static void gdt_set_gate(int num, uint32_t base, uint32_t limit, 
                         uint8_t access, uint8_t gran) {
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;
    
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[num].access = access;
}

/**
 * gdt_init - Initialize the Global Descriptor Table
 */
void gdt_init(void) {
    gp.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gp.base = (uint32_t)&gdt;
    
    // Null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);
    
    // Code segment: base=0, limit=4GB, access=0x9A, granularity=0xCF
    // Access: present, ring 0, code segment, executable, readable
    // Granularity: 4KB blocks, 32-bit
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    
    // Data segment: base=0, limit=4GB, access=0x92, granularity=0xCF
    // Access: present, ring 0, data segment, writable
    // Granularity: 4KB blocks, 32-bit
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    // Load the GDT
    gdt_flush((uint32_t)&gp);
}

