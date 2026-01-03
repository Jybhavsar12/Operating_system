/**
 * shell.h - Shell interface
 */

#ifndef SHELL_H
#define SHELL_H

/**
 * shell_init - Initialize the shell
 */
void shell_init(void);

/**
 * shell_handle_input - Handle a character of input
 * @c: Character to handle
 */
void shell_handle_input(char c);

#endif // SHELL_H

