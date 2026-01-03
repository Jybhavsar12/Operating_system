/**
 * desktop.h - Desktop environment interface
 */

#ifndef DESKTOP_H
#define DESKTOP_H

#include "types.h"

/**
 * desktop_init - Initialize desktop environment
 */
void desktop_init(void);

/**
 * desktop_draw - Draw the desktop
 */
void desktop_draw(void);

/**
 * desktop_draw_icon - Draw a desktop icon
 * @x: X position
 * @y: Y position
 * @label: Icon label
 * @color: Icon color
 */
void desktop_draw_icon(int x, int y, const char *label, uint8_t color);

/**
 * desktop_handle_key - Handle keyboard input
 * @c: Character pressed
 */
void desktop_handle_key(char c);

/**
 * desktop_show_about - Show about dialog
 */
void desktop_show_about(void);

#endif // DESKTOP_H

