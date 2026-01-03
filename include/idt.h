/**
 * idt.h - Interrupt Descriptor Table interface
 */

#ifndef IDT_H
#define IDT_H

#include "types.h"

/**
 * idt_init - Initialize the Interrupt Descriptor Table
 */
void idt_init(void);

/**
 * idt_set_gate - Set an IDT entry
 * @num: Interrupt number
 * @base: Address of interrupt handler
 * @selector: Code segment selector
 * @flags: Flags (present, privilege level, gate type)
 */
void idt_set_gate(uint8_t num, uint32_t base, uint16_t selector, uint8_t flags);

#endif // IDT_H

