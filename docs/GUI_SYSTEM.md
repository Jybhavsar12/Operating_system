# SimpleOS GUI System

## Overview

SimpleOS now features a complete graphical user interface (GUI) system with:
- **VGA Graphics Mode** - 320x200 resolution, 256 colors
- **Login Screen** - User authentication before accessing the desktop
- **Desktop Environment** - Graphical desktop with windows and icons
- **GUI Framework** - Windows, buttons, textboxes, and labels

## Features

### 1. VGA Graphics Driver

The VGA driver provides low-level graphics primitives:

- **Resolution**: 320x200 pixels
- **Colors**: 256-color palette
- **Drawing Functions**:
  - `vga_put_pixel()` - Draw individual pixels
  - `vga_draw_line()` - Draw lines
  - `vga_draw_rect()` - Draw filled rectangles
  - `vga_draw_rect_outline()` - Draw rectangle borders
  - `vga_clear_screen()` - Clear screen with color

### 2. Font System

8x8 pixel bitmap font for text rendering:

- **Character Set**: ASCII 32-126
- **Functions**:
  - `font_draw_char()` - Draw single character
  - `font_draw_string()` - Draw text strings
- **Features**:
  - Transparent background support
  - Customizable text and background colors

### 3. GUI Framework

Complete widget system for building interfaces:

#### Windows
- Title bar with window title
- Close button (X)
- Movable and resizable (future enhancement)
- Border and shadow effects

#### Buttons
- Click detection
- Hover effects
- Pressed state visualization
- Callback function support

#### Textboxes
- Text input with cursor
- Password mode (shows asterisks)
- Focus indication
- Backspace support
- Tab navigation

#### Labels
- Static text display
- Customizable colors
- Transparent background

### 4. Login System

Secure login screen before desktop access:

- **Default Credentials**:
  - Username: `admin`
  - Password: `password`

- **Features**:
  - Tab navigation between fields
  - Password masking
  - Error messages for invalid credentials
  - Enter key to submit

- **Keyboard Controls**:
  - `Tab` - Switch between username and password
  - `Enter` - Attempt login
  - `Backspace` - Delete characters
  - `A-Z, 0-9` - Type credentials

### 5. Desktop Environment

Graphical desktop after successful login:

- **Welcome Window** - Greeting message
- **Desktop Icons**:
  - Terminal (future: launch text mode)
  - Files (future: file browser)
  - Settings (future: system settings)

- **Taskbar**:
  - Application name
  - Clock display (placeholder)
  - System tray (future)

- **Buttons**:
  - About - Show system information
  - Shutdown - Power off system (future)

## Architecture

### Component Hierarchy

```
kernel/
├── drivers/
│   ├── vga.c          # VGA graphics driver
│   ├── font.c         # Bitmap font renderer
│   └── keyboard.c     # Keyboard input (updated for GUI)
└── gui/
    ├── gui.c          # GUI framework (widgets)
    ├── login.c        # Login screen
    └── desktop.c      # Desktop environment
```

### Data Flow

```
Keyboard Input
    ↓
keyboard_handler()
    ↓
[Mode Router]
    ├→ SHELL mode → shell_handle_input()
    ├→ LOGIN mode → login_handle_key()
    └→ DESKTOP mode → desktop_handle_key()
```

## Usage

### Switching Between Text and GUI Mode

Edit `kernel/kernel.c`:

```c
// Change this line:
static int boot_mode = BOOT_MODE_GUI;  // GUI mode (default)

// To this for text mode:
static int boot_mode = BOOT_MODE_TEXT;  // Text mode (shell)
```

### Building and Running

```bash
# Build the OS
make clean && make all

# Run in QEMU
make run

# The login screen will appear
# Enter: admin / password
# Press Enter to login
```

### Login Screen Controls

1. **Type username** in the first field
2. **Press Tab** to move to password field
3. **Type password** (shown as asterisks)
4. **Press Enter** to login
5. **On success**: Desktop appears
6. **On failure**: Error message shown, password cleared

## Color Palette

Common VGA colors available:

| Color | Value | Usage |
|-------|-------|-------|
| Black | 0x00 | Text, borders |
| Blue | 0x01 | Title bars |
| Cyan | 0x03 | Desktop background |
| Red | 0x04 | Close buttons, errors |
| Dark Gray | 0x08 | Taskbar, shadows |
| Light Gray | 0x07 | Window backgrounds |
| White | 0x0F | Text on dark backgrounds |
| Yellow | 0x0E | Icons, highlights |

## API Reference

### VGA Functions

```c
// Initialize graphics mode
void vga_set_mode(uint8_t mode);

// Drawing primitives
void vga_put_pixel(int x, int y, uint8_t color);
void vga_draw_line(int x1, int y1, int x2, int y2, uint8_t color);
void vga_draw_rect(int x, int y, int width, int height, uint8_t color);
void vga_clear_screen(uint8_t color);
```

### Font Functions

```c
// Draw text
void font_draw_char(char c, int x, int y, uint8_t color, uint8_t bg_color);
void font_draw_string(const char *str, int x, int y, uint8_t color, uint8_t bg_color);
```

### GUI Functions

```c
// Initialize GUI system
void gui_init(void);

// Draw widgets
void gui_draw_window(window_t *win);
void gui_draw_button(button_t *btn);
void gui_draw_textbox(textbox_t *box);
void gui_draw_label(label_t *label);

// Interaction
bool gui_button_is_clicked(button_t *btn, int x, int y);
void gui_textbox_add_char(textbox_t *box, char c);
void gui_textbox_backspace(textbox_t *box);
```

## Future Enhancements

### Planned Features

- [ ] **Mouse Support** - PS/2 mouse driver for clicking
- [ ] **Window Management** - Drag, resize, minimize windows
- [ ] **File Browser** - Graphical file explorer
- [ ] **Terminal Emulator** - GUI terminal window
- [ ] **Settings Panel** - System configuration GUI
- [ ] **Multi-user Support** - Multiple user accounts
- [ ] **Encrypted Passwords** - Hash passwords securely
- [ ] **Screen Saver** - Idle screen animation
- [ ] **Themes** - Customizable color schemes
- [ ] **Icons** - Better icon graphics
- [ ] **Menus** - Drop-down and context menus
- [ ] **Dialogs** - Alert, confirm, prompt dialogs

### Technical Improvements

- [ ] **Double Buffering** - Eliminate screen flicker
- [ ] **Higher Resolutions** - VESA modes (640x480, 800x600)
- [ ] **True Color** - 16-bit or 24-bit color depth
- [ ] **Hardware Acceleration** - GPU support
- [ ] **Anti-aliasing** - Smooth fonts and graphics
- [ ] **Transparency** - Alpha blending
- [ ] **Animations** - Smooth transitions

## Troubleshooting

### Login Screen Not Appearing

**Problem**: Black screen or text mode instead of GUI

**Solutions**:
1. Check `boot_mode` in `kernel/kernel.c` is set to `BOOT_MODE_GUI`
2. Rebuild: `make clean && make all`
3. Verify VGA mode is supported by your emulator

### Can't Type in Login Screen

**Problem**: Keyboard input not working

**Solutions**:
1. Check keyboard mode is set to `KEYBOARD_MODE_LOGIN`
2. Verify keyboard driver is initialized
3. Check IRQ1 is enabled

### Graphics Corrupted

**Problem**: Garbled or incorrect graphics

**Solutions**:
1. VGA memory might be corrupted
2. Try restarting QEMU
3. Check VGA mode initialization

### Login Always Fails

**Problem**: Correct credentials rejected

**Solutions**:
1. Default is `admin` / `password` (case-sensitive)
2. Check `strcmp()` function is working
3. Verify textbox is capturing input correctly

## Performance

### Benchmarks

- **Boot Time**: ~2 seconds to login screen
- **Login Time**: Instant (no encryption yet)
- **Screen Refresh**: ~60 FPS (no double buffering)
- **Memory Usage**: ~100 KB for GUI system

### Optimization Tips

1. **Minimize Redraws** - Only redraw changed areas
2. **Use Double Buffering** - Draw to off-screen buffer first
3. **Cache Rendered Text** - Don't re-render static text
4. **Optimize Loops** - Use efficient drawing algorithms

## Security Notes

⚠️ **WARNING**: This is an educational OS. The login system is NOT secure:

- Passwords stored in plain text
- No encryption
- No brute-force protection
- No session management
- Default credentials are public

**For learning purposes only!** Do not use in production.

## Credits

- **VGA Programming**: OSDev Wiki
- **Font**: Based on IBM VGA 8x8 font
- **GUI Design**: Inspired by classic desktop environments
- **Author**: Jyot Bhavsar

## License

Educational use only. Part of SimpleOS project.

---

**Next Steps**: Try the GUI system, experiment with colors, and explore the code!

