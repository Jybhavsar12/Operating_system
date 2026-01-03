/**
 * desktop.c - GUI desktop environment
 * Appears after successful login
 */

#include "../../include/desktop.h"
#include "../../include/gui.h"
#include "../../include/vga.h"
#include "../../include/font.h"
#include "../../include/memory.h"

// Desktop state
static bool desktop_initialized = false;

// GUI elements
static window_t welcome_window;
static label_t welcome_label;
static label_t info_label1;
static label_t info_label2;
static label_t info_label3;
static button_t about_button;
static button_t shutdown_button;

// Taskbar
static int taskbar_height = 20;

/**
 * desktop_init - Initialize desktop environment
 */
void desktop_init(void) {
    if (desktop_initialized) return;
    
    // Setup welcome window
    welcome_window.x = 50;
    welcome_window.y = 30;
    welcome_window.width = 220;
    welcome_window.height = 140;
    strcpy(welcome_window.title, "Welcome!");
    welcome_window.visible = true;
    welcome_window.active = true;
    
    // Setup welcome label
    welcome_label.x = 80;
    welcome_label.y = 55;
    strcpy(welcome_label.text, "Welcome to SimpleOS!");
    welcome_label.color = VGA_COLOR_BLACK;
    welcome_label.visible = true;
    
    // Setup info labels
    info_label1.x = 60;
    info_label1.y = 75;
    strcpy(info_label1.text, "You are now logged in.");
    info_label1.color = VGA_COLOR_BLACK;
    info_label1.visible = true;
    
    info_label2.x = 60;
    info_label2.y = 90;
    strcpy(info_label2.text, "This is a graphical");
    info_label2.color = VGA_COLOR_BLACK;
    info_label2.visible = true;
    
    info_label3.x = 60;
    info_label3.y = 105;
    strcpy(info_label3.text, "desktop environment!");
    info_label3.color = VGA_COLOR_BLACK;
    info_label3.visible = true;
    
    // Setup About button
    about_button.x = 70;
    about_button.y = 130;
    about_button.width = 70;
    about_button.height = 25;
    strcpy(about_button.text, "About");
    about_button.visible = true;
    about_button.pressed = false;
    about_button.hovered = false;
    
    // Setup Shutdown button
    shutdown_button.x = 150;
    shutdown_button.y = 130;
    shutdown_button.width = 100;
    shutdown_button.height = 25;
    strcpy(shutdown_button.text, "Shutdown");
    shutdown_button.visible = true;
    shutdown_button.pressed = false;
    shutdown_button.hovered = false;
    
    desktop_initialized = true;
}

/**
 * desktop_draw - Draw the desktop
 */
void desktop_draw(void) {
    // Clear screen with desktop background
    vga_clear_screen(VGA_COLOR_CYAN);
    
    // Draw taskbar at bottom
    vga_draw_rect(0, VGA_HEIGHT - taskbar_height, VGA_WIDTH, taskbar_height, VGA_COLOR_DARK_GRAY);
    vga_draw_line(0, VGA_HEIGHT - taskbar_height, VGA_WIDTH, VGA_HEIGHT - taskbar_height, VGA_COLOR_WHITE);
    
    // Draw taskbar text
    font_draw_string("SimpleOS Desktop", 5, VGA_HEIGHT - taskbar_height + 6, VGA_COLOR_WHITE, VGA_COLOR_DARK_GRAY);
    
    // Draw time (placeholder)
    font_draw_string("12:00", VGA_WIDTH - 45, VGA_HEIGHT - taskbar_height + 6, VGA_COLOR_WHITE, VGA_COLOR_DARK_GRAY);
    
    // Draw welcome window and its contents
    gui_draw_window(&welcome_window);
    gui_draw_label(&welcome_label);
    gui_draw_label(&info_label1);
    gui_draw_label(&info_label2);
    gui_draw_label(&info_label3);
    gui_draw_button(&about_button);
    gui_draw_button(&shutdown_button);
    
    // Draw desktop icons
    desktop_draw_icon(10, 10, "Terminal", VGA_COLOR_WHITE);
    desktop_draw_icon(10, 70, "Files", VGA_COLOR_YELLOW);
    desktop_draw_icon(10, 130, "Settings", VGA_COLOR_LIGHT_GRAY);
}

/**
 * desktop_draw_icon - Draw a desktop icon
 * @x: X position
 * @y: Y position
 * @label: Icon label
 * @color: Icon color
 */
void desktop_draw_icon(int x, int y, const char *label, uint8_t color) {
    // Draw icon background (simple rectangle)
    vga_draw_rect(x, y, 48, 48, color);
    vga_draw_rect_outline(x, y, 48, 48, VGA_COLOR_BLACK);
    
    // Draw icon symbol (simple pattern)
    vga_draw_rect(x + 12, y + 12, 24, 24, VGA_COLOR_DARK_GRAY);
    
    // Draw label below icon
    int label_len = strlen(label);
    int label_x = x + (48 - label_len * 8) / 2;
    font_draw_string(label, label_x, y + 52, VGA_COLOR_BLACK, 0xFF);
}

/**
 * desktop_handle_key - Handle keyboard input in desktop
 * @c: Character pressed
 */
void desktop_handle_key(char c) {
    // For now, just redraw
    // In a full implementation, this would handle keyboard shortcuts
    (void)c; // Unused parameter
}

/**
 * desktop_show_about - Show about dialog
 */
void desktop_show_about(void) {
    // Create about window
    window_t about_win;
    about_win.x = 70;
    about_win.y = 50;
    about_win.width = 180;
    about_win.height = 100;
    strcpy(about_win.title, "About SimpleOS");
    about_win.visible = true;
    
    // Redraw desktop
    desktop_draw();
    
    // Draw about window on top
    gui_draw_window(&about_win);
    
    // Draw about text
    font_draw_string("SimpleOS v0.2.0", 90, 75, VGA_COLOR_BLACK, 0xFF);
    font_draw_string("Educational OS", 90, 90, VGA_COLOR_BLACK, 0xFF);
    font_draw_string("with GUI!", 105, 105, VGA_COLOR_BLACK, 0xFF);
    font_draw_string("(c) 2026", 110, 120, VGA_COLOR_DARK_GRAY, 0xFF);
}

