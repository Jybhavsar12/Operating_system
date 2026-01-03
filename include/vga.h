/**
 * vga.h - VGA graphics mode interface
 */

#ifndef VGA_H
#define VGA_H

#include "types.h"

// VGA Text mode dimensions (used for GUI)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Common VGA colors (256-color palette)
#define VGA_COLOR_BLACK         0x00
#define VGA_COLOR_BLUE          0x01
#define VGA_COLOR_GREEN         0x02
#define VGA_COLOR_CYAN          0x03
#define VGA_COLOR_RED           0x04
#define VGA_COLOR_MAGENTA       0x05
#define VGA_COLOR_BROWN         0x06
#define VGA_COLOR_LIGHT_GRAY    0x07
#define VGA_COLOR_DARK_GRAY     0x08
#define VGA_COLOR_LIGHT_BLUE    0x09
#define VGA_COLOR_LIGHT_GREEN   0x0A
#define VGA_COLOR_LIGHT_CYAN    0x0B
#define VGA_COLOR_LIGHT_RED     0x0C
#define VGA_COLOR_LIGHT_MAGENTA 0x0D
#define VGA_COLOR_YELLOW        0x0E
#define VGA_COLOR_WHITE         0x0F

/**
 * vga_set_mode - Switch to VGA graphics mode
 * @mode: VGA mode number (0x13 for 320x200)
 */
void vga_set_mode(uint8_t mode);

/**
 * vga_clear_screen - Clear screen with color
 * @color: Fill color
 */
void vga_clear_screen(uint8_t color);

/**
 * vga_put_pixel - Draw a pixel
 * @x: X coordinate (0-319)
 * @y: Y coordinate (0-199)
 * @color: Pixel color
 */
void vga_put_pixel(int x, int y, uint8_t color);

/**
 * vga_get_pixel - Get pixel color
 * @x: X coordinate
 * @y: Y coordinate
 *
 * Return: Color at pixel
 */
uint8_t vga_get_pixel(int x, int y);

/**
 * vga_draw_line - Draw a line
 * @x1, y1: Start point
 * @x2, y2: End point
 * @color: Line color
 */
void vga_draw_line(int x1, int y1, int x2, int y2, uint8_t color);

/**
 * vga_draw_rect - Draw filled rectangle
 * @x, y: Top-left corner
 * @width, height: Dimensions
 * @color: Fill color
 */
void vga_draw_rect(int x, int y, int width, int height, uint8_t color);

/**
 * vga_draw_rect_outline - Draw rectangle outline
 * @x, y: Top-left corner
 * @width, height: Dimensions
 * @color: Border color
 */
void vga_draw_rect_outline(int x, int y, int width, int height, uint8_t color);

/**
 * vga_set_color - Set current drawing color
 * @color: Color to use
 */
void vga_set_color(uint8_t color);

/**
 * vga_get_color - Get current drawing color
 *
 * Return: Current color
 */
uint8_t vga_get_color(void);

#endif // VGA_H

