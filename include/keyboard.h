/**
 * keyboard.h - Keyboard driver interface
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
#include "isr.h"

/**
 * keyboard_init - Initialize keyboard driver
 */
void keyboard_init(void);

/**
 * keyboard_handler - IRQ1 interrupt handler for keyboard
 * @regs: Register state
 */
void keyboard_handler(registers_t regs);

#endif // KEYBOARD_H

