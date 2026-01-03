/**
 * keyboard.h - Keyboard driver interface
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "types.h"
#include "isr.h"

// Keyboard input modes
typedef enum {
    KEYBOARD_MODE_SHELL,
    KEYBOARD_MODE_LOGIN,
    KEYBOARD_MODE_DESKTOP
} keyboard_mode_t;

/**
 * keyboard_init - Initialize keyboard driver
 */
void keyboard_init(void);

/**
 * keyboard_handler - IRQ1 interrupt handler for keyboard
 * @regs: Register state
 */
void keyboard_handler(registers_t regs);

/**
 * keyboard_set_mode - Set keyboard input mode
 * @mode: New mode
 */
void keyboard_set_mode(keyboard_mode_t mode);

/**
 * keyboard_get_mode - Get current keyboard mode
 *
 * Return: Current mode
 */
keyboard_mode_t keyboard_get_mode(void);

#endif // KEYBOARD_H

