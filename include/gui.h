/**
 * gui.h - GUI framework interface
 */

#ifndef GUI_H
#define GUI_H

#include "types.h"

// Window structure
typedef struct {
    int x, y;
    int width, height;
    char title[64];
    bool visible;
    bool active;
} window_t;

// Button structure
typedef struct {
    int x, y;
    int width, height;
    char text[32];
    bool visible;
    bool pressed;
    bool hovered;
    void (*on_click)(void);
} button_t;

// Textbox structure
typedef struct {
    int x, y;
    int width, height;
    char text[64];
    int text_len;
    int max_len;
    bool visible;
    bool focused;
    bool password_mode;
} textbox_t;

// Label structure
typedef struct {
    int x, y;
    char text[128];
    uint8_t color;
    bool visible;
} label_t;

/**
 * gui_init - Initialize GUI system
 */
void gui_init(void);

/**
 * gui_draw_window - Draw a window
 * @win: Window to draw
 */
void gui_draw_window(window_t *win);

/**
 * gui_draw_button - Draw a button
 * @btn: Button to draw
 */
void gui_draw_button(button_t *btn);

/**
 * gui_draw_textbox - Draw a textbox
 * @box: Textbox to draw
 */
void gui_draw_textbox(textbox_t *box);

/**
 * gui_draw_label - Draw a label
 * @label: Label to draw
 */
void gui_draw_label(label_t *label);

/**
 * gui_button_is_clicked - Check if button is clicked
 * @btn: Button to check
 * @x: Mouse X coordinate
 * @y: Mouse Y coordinate
 *
 * Return: true if clicked
 */
bool gui_button_is_clicked(button_t *btn, int x, int y);

/**
 * gui_textbox_add_char - Add character to textbox
 * @box: Textbox
 * @c: Character to add
 */
void gui_textbox_add_char(textbox_t *box, char c);

/**
 * gui_textbox_backspace - Remove last character
 * @box: Textbox
 */
void gui_textbox_backspace(textbox_t *box);

#endif // GUI_H

