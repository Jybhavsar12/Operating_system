/**
 * font.h - Bitmap font interface
 */

#ifndef FONT_H
#define FONT_H

#include "types.h"

#define FONT_WIDTH 1
#define FONT_HEIGHT 1

/**
 * font_draw_char - Draw a character
 * @c: Character to draw
 * @x: X position
 * @y: Y position
 * @color: Text color
 * @bg_color: Background color (0xFF for transparent)
 */
void font_draw_char(char c, int x, int y, uint8_t color, uint8_t bg_color);

/**
 * font_draw_string - Draw a string
 * @str: String to draw
 * @x: X position
 * @y: Y position
 * @color: Text color
 * @bg_color: Background color (0xFF for transparent)
 */
void font_draw_string(const char *str, int x, int y, uint8_t color, uint8_t bg_color);

#endif // FONT_H

