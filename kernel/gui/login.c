/**
 * login.c - GUI login screen
 * Provides user authentication interface
 */

#include "../../include/login.h"
#include "../../include/gui.h"
#include "../../include/vga.h"
#include "../../include/font.h"
#include "../../include/memory.h"
#include "../../include/keyboard.h"

// Login state
static bool login_active = true;
static bool login_successful = false;

// Default credentials (in real OS, these would be hashed and stored securely)
#define DEFAULT_USERNAME "admin"
#define DEFAULT_PASSWORD "password"

// GUI elements
static window_t login_window;
static label_t title_label;
static label_t username_label;
static label_t password_label;
static label_t error_label;
static textbox_t username_box;
static textbox_t password_box;
static button_t login_button;

// Current focused textbox
static textbox_t *focused_box = NULL;

/**
 * login_init - Initialize login screen
 */
void login_init(void) {
    // Initialize GUI
    gui_init();
    
    // Setup login window (adjusted for 80x25 text mode)
    login_window.x = 15;
    login_window.y = 3;
    login_window.width = 50;
    login_window.height = 18;
    strcpy(login_window.title, "SimpleOS Login");
    login_window.visible = true;
    login_window.active = true;

    // Setup title label
    title_label.x = 20;
    title_label.y = 6;
    strcpy(title_label.text, "Welcome to SimpleOS");
    title_label.color = VGA_COLOR_WHITE;
    title_label.visible = true;

    // Setup username label
    username_label.x = 20;
    username_label.y = 9;
    strcpy(username_label.text, "Username:");
    username_label.color = VGA_COLOR_WHITE;
    username_label.visible = true;

    // Setup username textbox
    username_box.x = 20;
    username_box.y = 10;
    username_box.width = 40;
    username_box.height = 1;
    username_box.text[0] = '\0';
    username_box.text_len = 0;
    username_box.max_len = 32;
    username_box.visible = true;
    username_box.focused = true;
    username_box.password_mode = false;
    focused_box = &username_box;

    // Setup password label
    password_label.x = 20;
    password_label.y = 13;
    strcpy(password_label.text, "Password:");
    password_label.color = VGA_COLOR_WHITE;
    password_label.visible = true;

    // Setup password textbox
    password_box.x = 20;
    password_box.y = 14;
    password_box.width = 40;
    password_box.height = 1;
    password_box.text[0] = '\0';
    password_box.text_len = 0;
    password_box.max_len = 32;
    password_box.visible = true;
    password_box.focused = false;
    password_box.password_mode = true;

    // Setup login button
    login_button.x = 35;
    login_button.y = 17;
    login_button.width = 10;
    login_button.height = 1;
    strcpy(login_button.text, "Login");
    login_button.visible = true;
    login_button.pressed = false;
    login_button.hovered = false;

    // Setup error label (initially hidden)
    error_label.x = 20;
    error_label.y = 19;
    strcpy(error_label.text, "");
    error_label.color = VGA_COLOR_RED;
    error_label.visible = false;
}

/**
 * login_draw - Draw the login screen
 */
void login_draw(void) {
    // Clear screen
    vga_clear_screen(VGA_COLOR_BLUE);

    // Draw all GUI elements
    gui_draw_window(&login_window);
    gui_draw_label(&title_label);
    gui_draw_label(&username_label);
    gui_draw_textbox(&username_box);
    gui_draw_label(&password_label);
    gui_draw_textbox(&password_box);
    gui_draw_button(&login_button);
    gui_draw_label(&error_label);

    // Draw hint at bottom
    font_draw_string("Hint: admin/password", 20, 22, VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLUE);
}

/**
 * login_handle_key - Handle keyboard input
 * @c: Character pressed
 */
void login_handle_key(char c) {
    if (!login_active) return;

    // DEBUG: Flash the window title to show keyboard is working
    static int key_count = 0;
    key_count++;

    if (c == '\t') {
        // Tab: Switch focus between textboxes
        if (focused_box == &username_box) {
            username_box.focused = false;
            password_box.focused = true;
            focused_box = &password_box;
        } else {
            password_box.focused = false;
            username_box.focused = true;
            focused_box = &username_box;
        }
    } else if (c == '\n') {
        // Enter: Attempt login
        login_attempt();
    } else if (c == '\b') {
        // Backspace
        if (focused_box) {
            gui_textbox_backspace(focused_box);
        }
    } else if (c >= 32 && c <= 126) {
        // Regular character
        if (focused_box) {
            gui_textbox_add_char(focused_box, c);
        }
    }
    
    // Redraw screen
    login_draw();
}

/**
 * login_attempt - Attempt to log in with current credentials
 */
void login_attempt(void) {
    // Check credentials
    if (strcmp(username_box.text, DEFAULT_USERNAME) == 0 &&
        strcmp(password_box.text, DEFAULT_PASSWORD) == 0) {
        // Login successful!
        login_successful = true;
        login_active = false;
    } else {
        // Login failed
        strcpy(error_label.text, "Invalid credentials!");
        error_label.visible = true;
        
        // Clear password
        password_box.text[0] = '\0';
        password_box.text_len = 0;
    }
}

/**
 * login_is_successful - Check if login was successful
 *
 * Return: true if logged in
 */
bool login_is_successful(void) {
    return login_successful;
}

/**
 * login_is_active - Check if login screen is active
 *
 * Return: true if login screen is showing
 */
bool login_is_active(void) {
    return login_active;
}

