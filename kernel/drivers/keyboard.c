/**
 * keyboard.c - PS/2 Keyboard driver
 * Handles keyboard input via IRQ1
 */

#include "../../include/keyboard.h"
#include "../../include/ports.h"
#include "../../include/screen.h"
#include "../../include/isr.h"
#include "../../include/shell.h"

// Scancode to ASCII mapping (US keyboard layout)
const char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

// Shifted characters
const char scancode_to_ascii_shift[] = {
    0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',
    0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
    0, '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', 0,
    '*', 0, ' '
};

static int shift_pressed = 0;
static keyboard_mode_t current_mode = KEYBOARD_MODE_SHELL;

/**
 * keyboard_handler - IRQ1 interrupt handler for keyboard
 * @regs: Register state (unused)
 */
void keyboard_handler(registers_t regs) {
    uint8_t scancode = port_byte_in(0x60);

    // Handle shift keys
    if (scancode == 0x2A || scancode == 0x36) {
        shift_pressed = 1;
        return;
    }
    if (scancode == 0xAA || scancode == 0xB6) {
        shift_pressed = 0;
        return;
    }

    // Ignore key release events (scancode >= 0x80)
    if (scancode >= 0x80) {
        return;
    }

    // Convert scancode to ASCII
    char c;
    if (scancode < sizeof(scancode_to_ascii)) {
        if (shift_pressed) {
            c = scancode_to_ascii_shift[scancode];
        } else {
            c = scancode_to_ascii[scancode];
        }

        if (c != 0) {
            // Route input to shell
            shell_handle_input(c);
        }
    }
}

/**
 * keyboard_set_mode - Set keyboard input mode
 * @mode: New keyboard mode
 */
void keyboard_set_mode(keyboard_mode_t mode) {
    current_mode = mode;
}

/**
 * keyboard_get_mode - Get current keyboard mode
 *
 * Return: Current mode
 */
keyboard_mode_t keyboard_get_mode(void) {
    return current_mode;
}

/**
 * keyboard_init - Initialize keyboard driver
 */
void keyboard_init(void) {
    // Keyboard uses IRQ1 (interrupt 33)
    // Handler will be registered through IRQ system
    current_mode = KEYBOARD_MODE_SHELL;
}

