# SimpleOS Screenshots

## GUI Mode (Default)

### Login Screen

The login screen is the first thing you see when booting SimpleOS in GUI mode:

**Features:**
- Blue title bar with "SimpleOS Login"
- Username and password input fields
- Tab navigation between fields
- Password masking (shows asterisks)
- Login button
- Error messages for invalid credentials
- Hint showing default credentials

**Default Credentials:**
- Username: `admin`
- Password: `password`

**Controls:**
- Type to enter text
- `Tab` - Switch between username and password fields
- `Enter` - Submit login
- `Backspace` - Delete characters

---

### Desktop Environment

After successful login, you'll see the graphical desktop:

**Features:**
- Light cyan desktop background
- Welcome window with greeting message
- Desktop icons:
  - Terminal (white icon)
  - Files (yellow icon)
  - Settings (gray icon)
- Taskbar at bottom:
  - "SimpleOS Desktop" label
  - Clock display (12:00)
- Action buttons:
  - About button - Shows system information
  - Shutdown button - Power off (future feature)

**Window Features:**
- Blue title bar
- Window title text
- Red close button (X)
- Gray window background
- Black border

---

## Text Mode (Shell)

When booting in text mode, you'll see:

**Features:**
- Black background with white text
- Boot messages showing initialization
- Command prompt (>)
- Available commands:
  - `help` - Show available commands
  - `clear` - Clear the screen
  - `echo <text>` - Print text
  - `version` - Show OS version
  - `about` - Show system information

**Example Session:**
```
SimpleOS Kernel Loaded Successfully
Version 0.2.0 - Educational Operating System
Copyright (c) 2026 Jyot Bhavsar

Initializing GDT...
Initializing IDT...
Initializing ISR...
Initializing keyboard...
Initializing shell...

Kernel initialized in 32-bit protected mode
All systems operational.

Welcome to SimpleOS! Type 'help' for available commands.
> help
Available commands:
  help    - Show this help message
  clear   - Clear the screen
  echo    - Echo text to screen
  version - Show OS version
  about   - Show system information
> 
```

---

## How to Take Screenshots

### In QEMU

1. **Using QEMU Monitor:**
   ```bash
   # Press Ctrl+Alt+2 to enter QEMU monitor
   # Type:
   screendump screenshot.ppm
   # Press Ctrl+Alt+1 to return to OS
   ```

2. **Convert PPM to PNG:**
   ```bash
   convert screenshot.ppm screenshot.png
   ```

### Using VirtualBox

1. **Menu Method:**
   - View → Take Screenshot
   - Save as PNG

2. **Keyboard Shortcut:**
   - Host Key + E (usually Right Ctrl + E)

### Using VMware

1. **Menu Method:**
   - VM → Capture Screen
   - Save image

---

## Color Scheme

### GUI Mode Colors

| Element | Color | Hex Value |
|---------|-------|-----------|
| Desktop Background | Cyan | 0x03 |
| Window Background | Light Gray | 0x07 |
| Title Bar | Blue | 0x01 |
| Title Text | White | 0x0F |
| Close Button | Red | 0x04 |
| Taskbar | Dark Gray | 0x08 |
| Text | Black | 0x00 |
| Error Text | Red | 0x04 |

### Text Mode Colors

| Element | Color |
|---------|-------|
| Background | Black |
| Text | White |
| Prompt | White |

---

## Resolution and Display

### GUI Mode
- **Resolution:** 320x200 pixels
- **Color Depth:** 8-bit (256 colors)
- **VGA Mode:** Mode 13h
- **Aspect Ratio:** 16:10 (stretched to 4:3 on most displays)

### Text Mode
- **Resolution:** 80x25 characters
- **Character Size:** 8x16 pixels
- **Total Pixels:** 640x400
- **VGA Mode:** Mode 3 (text mode)

---

## Tips for Best Screenshots

1. **Use QEMU with scaling:**
   ```bash
   qemu-system-i386 -drive format=raw,file=build/os-image.bin -scale-to-fit
   ```

2. **Increase window size:**
   ```bash
   qemu-system-i386 -drive format=raw,file=build/os-image.bin -display gtk,zoom-to-fit=on
   ```

3. **Record video:**
   ```bash
   # Install ffmpeg first
   qemu-system-i386 -drive format=raw,file=build/os-image.bin \
     -device VGA -vga std \
     -display gtk \
     -monitor stdio
   ```

---

## Comparison: GUI vs Text Mode

| Feature | GUI Mode | Text Mode |
|---------|----------|-----------|
| Boot Time | ~2 seconds | ~1 second |
| Memory Usage | ~100 KB | ~50 KB |
| User Interface | Graphical | Command-line |
| Input Method | Keyboard | Keyboard |
| Resolution | 320x200 | 80x25 chars |
| Colors | 256 | 16 |
| Login Required | Yes | No |
| Ease of Use | Beginner-friendly | Power users |

---

## Future Screenshots

Coming soon:
- Mouse cursor
- File browser window
- Terminal emulator in GUI
- Settings panel
- Multiple windows
- Themes and customization

---

**Note:** To switch between modes, edit `kernel/kernel.c` and change the `boot_mode` variable, then rebuild.

