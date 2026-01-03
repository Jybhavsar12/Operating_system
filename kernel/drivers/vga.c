/**
 * vga.c - VGA graphics mode driver
 * Supports 320x200 256-color mode (Mode 13h)
 */

#include "../../include/vga.h"
#include "../../include/ports.h"
#include "../../include/memory.h"

// VGA memory address in Mode 13h
#define VGA_MEMORY 0xA0000
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

static uint8_t *vga_memory = (uint8_t *)VGA_MEMORY;
static uint8_t current_color = 0x0F; // White

/**
 * vga_set_mode - Switch to VGA graphics mode
 * @mode: VGA mode number (0x13 for 320x200 256-color)
 */
void vga_set_mode(uint8_t mode) {
    // Use BIOS interrupt to set video mode
    // In protected mode, we need to set registers directly
    
    if (mode == 0x13) {
        // Mode 13h: 320x200 256 colors
        // VGA registers setup for mode 13h
        
        // Miscellaneous Output Register
        port_byte_out(0x3C2, 0x63);
        
        // Sequencer Registers
        port_byte_out(0x3C4, 0x00); port_byte_out(0x3C5, 0x03);
        port_byte_out(0x3C4, 0x01); port_byte_out(0x3C5, 0x01);
        port_byte_out(0x3C4, 0x02); port_byte_out(0x3C5, 0x0F);
        port_byte_out(0x3C4, 0x03); port_byte_out(0x3C5, 0x00);
        port_byte_out(0x3C4, 0x04); port_byte_out(0x3C5, 0x0E);
        
        // CRTC Registers
        port_byte_out(0x3D4, 0x11); port_byte_out(0x3D5, 0x00);
        
        // Graphics mode is now active
    }
}

/**
 * vga_clear_screen - Clear the screen with a color
 * @color: Color to fill the screen with
 */
void vga_clear_screen(uint8_t color) {
    memset(vga_memory, color, VGA_WIDTH * VGA_HEIGHT);
}

/**
 * vga_put_pixel - Draw a pixel at specified coordinates
 * @x: X coordinate (0-319)
 * @y: Y coordinate (0-199)
 * @color: Color index (0-255)
 */
void vga_put_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        vga_memory[y * VGA_WIDTH + x] = color;
    }
}

/**
 * vga_get_pixel - Get pixel color at coordinates
 * @x: X coordinate
 * @y: Y coordinate
 *
 * Return: Color at that pixel
 */
uint8_t vga_get_pixel(int x, int y) {
    if (x >= 0 && x < VGA_WIDTH && y >= 0 && y < VGA_HEIGHT) {
        return vga_memory[y * VGA_WIDTH + x];
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
    for (int dy = 0; dy < height; dy++) {
        for (int dx = 0; dx < width; dx++) {
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

