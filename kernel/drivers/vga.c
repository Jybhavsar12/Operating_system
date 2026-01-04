/**
 * vga.c - VGA graphics mode driver (Text-mode based)
 * Uses VGA text mode to simulate graphics
 */

#include "../../include/vga.h"
#include "../../include/ports.h"
#include "../../include/memory.h"

// VGA text mode memory
#define VGA_TEXT_MEMORY 0xB8000
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Simulated graphics using text mode characters
static uint16_t *vga_memory = (uint16_t *)VGA_TEXT_MEMORY;
static uint8_t current_color = 0x0F; // White on black

// Character to use for "pixels" (full block)
#define PIXEL_CHAR 0xDB

/**
 * vga_set_mode - Initialize VGA for GUI
 * @mode: VGA mode (ignored, we use text mode)
 */
void vga_set_mode(uint8_t mode) {
    (void)mode; // We're already in text mode
    // Just clear the screen
    vga_clear_screen(VGA_COLOR_BLACK);
}

/**
 * vga_clear_screen - Clear the screen with a color
 * @color: Background color to fill
 */
void vga_clear_screen(uint8_t color) {
    // VGA text mode format: low byte = char, high byte = attribute
    // Attribute = (background << 4) | foreground
    uint8_t attribute = (color << 4) | VGA_COLOR_BLACK; // Background color, black text
    uint16_t blank = (attribute << 8) | ' ';
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_memory[i] = blank;
    }
}

/**
 * vga_put_pixel - Draw a "pixel" using text mode character
 * @x: X coordinate (0-79)
 * @y: Y coordinate (0-24)
 * @color: Color attribute (background color)
 */
void vga_put_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        int offset = y * VGA_WIDTH + x;
        // Use full block character with color as background
        uint8_t attribute = (color << 4) | color; // Same color for fg and bg
        vga_memory[offset] = (attribute << 8) | PIXEL_CHAR;
    }
}

/**
 * vga_get_pixel - Get pixel color at coordinates
 * @x: X coordinate
 * @y: Y coordinate
 *
 * Return: Color at that position
 */
uint8_t vga_get_pixel(int x, int y) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        int offset = y * VGA_WIDTH + x;
        return (vga_memory[offset] >> 8) & 0xFF;
    }
    return 0;
}

/**
 * vga_draw_line - Draw a line between two points
 * @x1, y1: Start point
 * @x2, y2: End point
 * @color: Line color
 */
void vga_draw_line(int x1, int y1, int x2, int y2, uint8_t color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = (dx > dy ? dx : dy);
    if (steps < 0) steps = -steps;
    
    float x_inc = (float)dx / steps;
    float y_inc = (float)dy / steps;
    
    float x = x1;
    float y = y1;
    
    for (int i = 0; i <= steps; i++) {
        vga_put_pixel((int)x, (int)y, color);
        x += x_inc;
        y += y_inc;
    }
}

/**
 * vga_draw_rect - Draw a filled rectangle
 * @x, y: Top-left corner
 * @width, height: Rectangle dimensions
 * @color: Fill color
 */
void vga_draw_rect(int x, int y, int width, int height, uint8_t color) {
    for (int dy = 0; dy < height && (y + dy) < VGA_HEIGHT; dy++) {
        for (int dx = 0; dx < width && (x + dx) < VGA_WIDTH; dx++) {
            vga_put_pixel(x + dx, y + dy, color);
        }
    }
}

/**
 * vga_draw_rect_outline - Draw rectangle outline
 * @x, y: Top-left corner
 * @width, height: Rectangle dimensions
 * @color: Border color
 */
void vga_draw_rect_outline(int x, int y, int width, int height, uint8_t color) {
    // Top and bottom
    vga_draw_line(x, y, x + width - 1, y, color);
    vga_draw_line(x, y + height - 1, x + width - 1, y + height - 1, color);
    
    // Left and right
    vga_draw_line(x, y, x, y + height - 1, color);
    vga_draw_line(x + width - 1, y, x + width - 1, y + height - 1, color);
}

/**
 * vga_set_color - Set current drawing color
 * @color: Color to use for subsequent operations
 */
void vga_set_color(uint8_t color) {
    current_color = color;
}

/**
 * vga_get_color - Get current drawing color
 *
 * Return: Current color
 */
uint8_t vga_get_color(void) {
    return current_color;
}

