/**
 * shell.c - Simple command-line shell
 * Provides basic command interpretation
 */

#include "../include/shell.h"
#include "../include/screen.h"
#include "../include/memory.h"

#define MAX_COMMAND_LENGTH 256

static char command_buffer[MAX_COMMAND_LENGTH];
static int command_index = 0;

/**
 * shell_init - Initialize the shell
 */
void shell_init(void) {
    command_index = 0;
    command_buffer[0] = '\0';
}

/**
 * shell_execute - Execute a shell command
 * @command: Command string to execute
 */
static void shell_execute(const char *command) {
    if (strcmp(command, "help") == 0) {
        print("\nAvailable commands:\n");
        print("  help    - Display this help message\n");
        print("  clear   - Clear the screen\n");
        print("  about   - Display system information\n");
        print("  echo    - Echo text back to screen\n");
        print("\n");
    }
    else if (strcmp(command, "clear") == 0) {
        clear_screen();
    }
    else if (strcmp(command, "about") == 0) {
        print("\nSimpleOS v0.1.0\n");
        print("Educational Operating System\n");
        print("Copyright (c) 2026 Jyot Bhavsar\n");
        print("\nFeatures:\n");
        print("  - 32-bit protected mode\n");
        print("  - VGA text mode driver\n");
        print("  - Keyboard input support\n");
        print("  - Interrupt handling (GDT, IDT, ISR)\n");
        print("  - Basic memory management\n");
        print("\n");
    }
    else if (command[0] == 'e' && command[1] == 'c' && command[2] == 'h' && command[3] == 'o') {
        // Echo command - print everything after "echo "
        if (command[4] == ' ') {
            print("\n");
            print(&command[5]);
            print("\n\n");
        } else {
            print("\n\n");
        }
    }
    else if (strlen(command) > 0) {
        print("\nUnknown command: ");
        print(command);
        print("\nType 'help' for available commands.\n\n");
    }
}

/**
 * shell_handle_input - Handle a character of input
 * @c: Character to handle
 */
void shell_handle_input(char c) {
    if (c == '\n') {
        // Execute command
        command_buffer[command_index] = '\0';
        shell_execute(command_buffer);
        
        // Reset command buffer
        command_index = 0;
        command_buffer[0] = '\0';
        
        // Print prompt
        print("> ");
    }
    else if (c == '\b') {
        // Backspace
        if (command_index > 0) {
            command_index--;
            command_buffer[command_index] = '\0';
            
            // Move cursor back and erase character
            int cursor = get_cursor();
            cursor -= 2;
            set_cursor(cursor);
            print_char(' ');
            set_cursor(cursor);
        }
    }
    else {
        // Add character to buffer
        if (command_index < MAX_COMMAND_LENGTH - 1) {
            command_buffer[command_index] = c;
            command_index++;
            print_char(c);
        }
    }
}

