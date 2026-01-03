/**
 * gui.c - Simple GUI framework
 * Provides windows, buttons, and text boxes
 */

#include "../../include/gui.h"
#include "../../include/vga.h"
#include "../../include/font.h"
#include "../../include/memory.h"

// GUI state
static bool gui_initialized = false;

/**
 * gui_init - Initialize GUI system
 */
void gui_init(void) {
    if (!gui_initialized) {
        vga_set_mode(0x03); // Text mode (already in it)
        vga_clear_screen(VGA_COLOR_BLUE); // Blue background
        gui_initialized = true;
    }
}

/**
 * gui_draw_window - Draw a window
 * @win: Window structure
 */
void gui_draw_window(window_t *win) {
    if (!win->visible) return;

    // Draw window background
    vga_draw_rect(win->x, win->y, win->width, win->height, VGA_COLOR_CYAN);

    // Draw title bar
    vga_draw_rect(win->x, win->y, win->width, 2, VGA_COLOR_LIGHT_BLUE);

    // Draw title text
    font_draw_string(win->title, win->x + 2, win->y + 1, VGA_COLOR_WHITE, VGA_COLOR_LIGHT_BLUE);

    // Draw window border
    vga_draw_rect_outline(win->x, win->y, win->width, win->height, VGA_COLOR_WHITE);

    // Draw close button (X) in top right
    int close_x = win->x + win->width - 3;
    int close_y = win->y + 1;
    font_draw_char('X', close_x, close_y, VGA_COLOR_YELLOW, VGA_COLOR_RED);
}

/**
 * gui_draw_button - Draw a button
 * @btn: Button structure
 */
void gui_draw_button(button_t *btn) {
    if (!btn->visible) return;

    uint8_t bg_color = btn->pressed ? VGA_COLOR_DARK_GRAY : VGA_COLOR_GREEN;
    uint8_t text_color = VGA_COLOR_BLACK;

    // Draw button background
    vga_draw_rect(btn->x, btn->y, btn->width, btn->height, bg_color);

    // Draw button text (centered)
    int text_len = strlen(btn->text);
    int text_x = btn->x + (btn->width - text_len) / 2;
    int text_y = btn->y;
    font_draw_string(btn->text, text_x, text_y, text_color, bg_color);
}

/**
 * gui_draw_textbox - Draw a text input box
 * @box: Textbox structure
 */
void gui_draw_textbox(textbox_t *box) {
    if (!box->visible) return;

    uint8_t bg_color = box->focused ? VGA_COLOR_WHITE : VGA_COLOR_LIGHT_GRAY;
    uint8_t text_color = VGA_COLOR_BLACK;

    // Draw textbox background
    vga_draw_rect(box->x, box->y, box->width, box->height, bg_color);

    // Draw text content
    if (box->password_mode) {
        // Show asterisks for password
        char masked[64];
        for (int i = 0; i < box->text_len && i < 63; i++) {
            masked[i] = '*';
        }
        masked[box->text_len] = '\0';
        font_draw_string(masked, box->x + 1, box->y, text_color, bg_color);
    } else {
        font_draw_string(box->text, box->x + 1, box->y, text_color, bg_color);
    }

    // Draw cursor if focused
    if (box->focused) {
        int cursor_x = box->x + 1 + box->text_len;
        int cursor_y = box->y;
        font_draw_char('_', cursor_x, cursor_y, text_color, bg_color);
    }
}

/**
 * gui_draw_label - Draw a text label
 * @label: Label structure
 */
void gui_draw_label(label_t *label) {
    if (!label->visible) return;

    font_draw_string(label->text, label->x, label->y, label->color, VGA_COLOR_CYAN);
}

/**
 * gui_button_is_clicked - Check if button is clicked at coordinates
 * @btn: Button to check
 * @x: Mouse X coordinate
 * @y: Mouse Y coordinate
 *
 * Return: true if button was clicked
 */
bool gui_button_is_clicked(button_t *btn, int x, int y) {
    if (!btn->visible) return false;
    
    return (x >= btn->x && x < btn->x + btn->width &&
            y >= btn->y && y < btn->y + btn->height);
}

/**
 * gui_textbox_add_char - Add character to textbox
 * @box: Textbox to modify
 * @c: Character to add
 */
void gui_textbox_add_char(textbox_t *box, char c) {
    if (box->text_len < box->max_len - 1) {
        box->text[box->text_len] = c;
        box->text_len++;
        box->text[box->text_len] = '\0';
    }
}

/**
 * gui_textbox_backspace - Remove last character from textbox
 * @box: Textbox to modify
 */
void gui_textbox_backspace(textbox_t *box) {
    if (box->text_len > 0) {
        box->text_len--;
        box->text[box->text_len] = '\0';
    }
}

