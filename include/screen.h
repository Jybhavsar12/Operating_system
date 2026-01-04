/**
 * screen.h - VGA text mode screen driver interface
 */

#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"

// Screen dimensions
#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80

// Color definitions
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHT_GRAY 7
#define DARK_GRAY 8
#define LIGHT_BLUE 9
#define LIGHT_GREEN 10
#define LIGHT_CYAN 11
#define LIGHT_RED 12
#define LIGHT_MAGENTA 13
#define YELLOW 14
#define WHITE 15

// Default color scheme
#define DEFAULT_COLOR (WHITE | (BLACK << 4))

/**
 * clear_screen - Clear the entire screen
 */
void clear_screen(void);

/**
 * print - Print a null-terminated string to screen
 * @str: String to print
 */
void print(const char *str);

/**
 * print_char - Print a single character at current cursor position
 * @c: Character to print
 */
void print_char(char c);

/**
 * print_at - Print a string at specific position
 * @str: String to print
 * @col: Column position (0-79)
 * @row: Row position (0-24)
 */
void print_at(const char *str, int col, int row);

/**
 * set_cursor - Set cursor position
 * @offset: Cursor offset in video memory
 */
void set_cursor(int offset);

/**
 * get_cursor - Get current cursor position
 *
 * Return: Current cursor offset
 */
int get_cursor(void);

/**
 * print_int - Print an integer to screen
 * @n: Integer to print
 */
void print_int(int n);

#endif // SCREEN_H

