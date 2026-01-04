/**
 * shell.c - Simple command-line shell
 * Provides basic command interpretation
 */

#include "../include/shell.h"
#include "../include/screen.h"
#include "../include/memory.h"
#include "../include/filesystem.h"

#define MAX_COMMAND_LENGTH 256

static char command_buffer[MAX_COMMAND_LENGTH];
static int command_index = 0;
static char write_mode_filename[MAX_FILENAME];
static bool in_write_mode = false;

/**
 * shell_init - Initialize the shell
 */
void shell_init(void) {
    command_index = 0;
    command_buffer[0] = '\0';
    in_write_mode = false;
    fs_init();
}

/**
 * shell_execute - Execute a shell command
 * @command: Command string to execute
 */
static void shell_execute(const char *command) {
    if (strcmp(command, "help") == 0) {
        print("\nAvailable commands:\n");
        print("  help         - Display this help message\n");
        print("  clear        - Clear the screen\n");
        print("  about        - Display system information\n");
        print("  echo <text>  - Echo text back to screen\n");
        print("  touch <file> - Create a new file\n");
        print("  write <file> - Write content to a file\n");
        print("  cat <file>   - Display file contents\n");
        print("  ls           - List all files\n");
        print("  rm <file>    - Delete a file\n");
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
    else if (strcmp(command, "ls") == 0) {
        // List files
        print("\n");
        fs_list();
        print("\n");
    }
    else if (command[0] == 't' && command[1] == 'o' && command[2] == 'u' && command[3] == 'c' && command[4] == 'h') {
        // Touch command - create file
        if (command[5] == ' ' && command[6] != '\0') {
            const char *filename = &command[6];
            if (fs_create(filename) == 0) {
                print("\nFile '");
                print(filename);
                print("' created successfully.\n\n");
            } else {
                print("\nError: Could not create file. File may already exist or no space available.\n\n");
            }
        } else {
            print("\nUsage: touch <filename>\n\n");
        }
    }
    else if (command[0] == 'w' && command[1] == 'r' && command[2] == 'i' && command[3] == 't' && command[4] == 'e') {
        // Write command - write to file
        if (command[5] == ' ' && command[6] != '\0') {
            const char *filename = &command[6];
            if (fs_exists(filename)) {
                strcpy(write_mode_filename, filename);
                in_write_mode = true;
                print("\nEnter content (type 'EOF' on new line to finish):\n");
            } else {
                print("\nError: File '");
                print(filename);
                print("' does not exist. Create it first with 'touch'.\n\n");
            }
        } else {
            print("\nUsage: write <filename>\n\n");
        }
    }
    else if (command[0] == 'c' && command[1] == 'a' && command[2] == 't') {
        // Cat command - read file
        if (command[3] == ' ' && command[4] != '\0') {
            const char *filename = &command[4];
            char buffer[MAX_FILE_SIZE];
            if (fs_read(filename, buffer, MAX_FILE_SIZE) >= 0) {
                print("\n");
                print(buffer);
                print("\n\n");
            } else {
                print("\nError: File '");
                print(filename);
                print("' not found.\n\n");
            }
        } else {
            print("\nUsage: cat <filename>\n\n");
        }
    }
    else if (command[0] == 'r' && command[1] == 'm') {
        // Remove command - delete file
        if (command[2] == ' ' && command[3] != '\0') {
            const char *filename = &command[3];
            if (fs_delete(filename) == 0) {
                print("\nFile '");
                print(filename);
                print("' deleted successfully.\n\n");
            } else {
                print("\nError: File '");
                print(filename);
                print("' not found.\n\n");
            }
        } else {
            print("\nUsage: rm <filename>\n\n");
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

        // Check if in write mode
        if (in_write_mode) {
            // Check for EOF marker
            if (strcmp(command_buffer, "EOF") == 0) {
                in_write_mode = false;
                print("\nFile saved.\n\n> ");
            } else {
                // Append to file content
                char current_content[MAX_FILE_SIZE];
                fs_read(write_mode_filename, current_content, MAX_FILE_SIZE);

                // Add newline if not first line
                if (strlen(current_content) > 0) {
                    int len = strlen(current_content);
                    if (len < MAX_FILE_SIZE - 2) {
                        current_content[len] = '\n';
                        current_content[len + 1] = '\0';
                    }
                }

                // Append new line
                int current_len = strlen(current_content);
                int command_len = strlen(command_buffer);
                if (current_len + command_len < MAX_FILE_SIZE - 1) {
                    for (int i = 0; i < command_len; i++) {
                        current_content[current_len + i] = command_buffer[i];
                    }
                    current_content[current_len + command_len] = '\0';
                }

                fs_write(write_mode_filename, current_content);
                print("\n");
            }
        } else {
            shell_execute(command_buffer);
            print("> ");
        }

        // Reset command buffer
        command_index = 0;
        command_buffer[0] = '\0';
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

