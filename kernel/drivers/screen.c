/**
 * screen.c - VGA text mode screen driver
 * Provides functions for printing text to the screen
 */

#include "../../include/screen.h"
#include "../../include/ports.h"

// Private function declarations
static int get_screen_offset(int col, int row);
static int get_offset_row(int offset);
static int get_offset_col(int offset);
static void set_char_at_offset(char c, int offset);
static int scroll_screen(int offset);

/**
 * clear_screen - Clear the entire screen
 */
void clear_screen(void) {
    int row, col;
    for (row = 0; row < MAX_ROWS; row++) {
        for (col = 0; col < MAX_COLS; col++) {
            set_char_at_offset(' ', get_screen_offset(col, row));
        }
    }
    set_cursor(get_screen_offset(0, 0));
}

/**
 * print - Print a null-terminated string to screen
 * @str: String to print
 */
void print(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        print_char(str[i]);
        i++;
    }
}

/**
 * print_char - Print a single character at current cursor position
 * @c: Character to print
 */
void print_char(char c) {
    int offset = get_cursor();
    
    if (c == '\n') {
        // Move to next line
        int row = get_offset_row(offset);
        offset = get_screen_offset(0, row + 1);
    } else {
        // Print character
        set_char_at_offset(c, offset);
        offset += 2;  // Move to next character position (char + attribute)
    }
    
    // Check if we need to scroll
    offset = scroll_screen(offset);
    
    // Update cursor
    set_cursor(offset);
}

/**
 * print_at - Print a string at specific position
 * @str: String to print
 * @col: Column position (0-79)
 * @row: Row position (0-24)
 */
void print_at(const char *str, int col, int row) {
    set_cursor(get_screen_offset(col, row));
    print(str);
}

/**
 * set_cursor - Set cursor position
 * @offset: Cursor offset in video memory
 */
void set_cursor(int offset) {
    offset /= 2;  // Convert from byte offset to character offset
    
    // Send high byte
    port_byte_out(0x3D4, 14);
    port_byte_out(0x3D5, (uint8_t)(offset >> 8));
    
    // Send low byte
    port_byte_out(0x3D4, 15);
    port_byte_out(0x3D5, (uint8_t)(offset & 0xFF));
}

/**
 * get_cursor - Get current cursor position
 *
 * Return: Current cursor offset
 */
int get_cursor(void) {
    // Request high byte
    port_byte_out(0x3D4, 14);
    int offset = port_byte_in(0x3D5) << 8;
    
    // Request low byte
    port_byte_out(0x3D4, 15);
    offset += port_byte_in(0x3D5);
    
    return offset * 2;  // Convert from character offset to byte offset
}

/**
 * get_screen_offset - Calculate video memory offset
 * @col: Column position
 * @row: Row position
 *
 * Return: Byte offset in video memory
 */
static int get_screen_offset(int col, int row) {
    return 2 * (row * MAX_COLS + col);
}

/**
 * get_offset_row - Get row from offset
 * @offset: Byte offset in video memory
 *
 * Return: Row number
 */
static int get_offset_row(int offset) {
    return offset / (2 * MAX_COLS);
}

/**
 * get_offset_col - Get column from offset
 * @offset: Byte offset in video memory
 *
 * Return: Column number
 */
static int get_offset_col(int offset) {
    return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

/**
 * set_char_at_offset - Write character to video memory
 * @c: Character to write
 * @offset: Byte offset in video memory
 */
static void set_char_at_offset(char c, int offset) {
    uint8_t *vidmem = (uint8_t *)VIDEO_ADDRESS;
    vidmem[offset] = c;
    vidmem[offset + 1] = DEFAULT_COLOR;
}

/**
 * scroll_screen - Scroll screen if necessary
 * @offset: Current cursor offset
 *
 * Return: Adjusted cursor offset
 */
static int scroll_screen(int offset) {
    // If cursor is within screen bounds, return
    if (offset < MAX_ROWS * MAX_COLS * 2) {
        return offset;
    }
    
    // Move all rows up by one
    int i;
    for (i = 1; i < MAX_ROWS; i++) {
        int src = get_screen_offset(0, i);
        int dst = get_screen_offset(0, i - 1);
        uint8_t *vidmem = (uint8_t *)VIDEO_ADDRESS;
        
        int j;
        for (j = 0; j < MAX_COLS * 2; j++) {
            vidmem[dst + j] = vidmem[src + j];
        }
    }
    
    // Clear last row
    int last_row = get_screen_offset(0, MAX_ROWS - 1);
    for (i = 0; i < MAX_COLS; i++) {
        set_char_at_offset(' ', last_row + i * 2);
    }
    
    // Move cursor to last row
    return get_screen_offset(0, MAX_ROWS - 1);
}

