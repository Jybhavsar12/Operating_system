/**
 * isr.h - Interrupt Service Routines interface
 */

#ifndef ISR_H
#define ISR_H

#include "types.h"

// Register structure passed to ISR handlers
typedef struct {
    uint32_t ds;                                    // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha
    uint32_t int_no, err_code;                      // Interrupt number and error code
    uint32_t eip, cs, eflags, useresp, ss;          // Pushed by processor automatically
} registers_t;

/**
 * isr_init - Initialize Interrupt Service Routines
 */
void isr_init(void);

/**
 * isr_handler - Common ISR handler
 * @regs: Register state at time of interrupt
 */
void isr_handler(registers_t regs);

/**
 * irq_handler - Common IRQ handler
 * @regs: Register state at time of interrupt
 */
void irq_handler(registers_t regs);

#endif // ISR_H

