# Changelog

All notable changes to SimpleOS will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.2.0] - 2026-01-03

### Added - GUI System 🎨

#### Graphics & Display
- **VGA Graphics Driver** - Mode 13h support (320x200, 256 colors)
- **Bitmap Font System** - 8x8 pixel font for text rendering
- **Drawing Primitives** - Pixels, lines, rectangles, and outlines
- **Color Palette** - Full 256-color VGA palette support

#### GUI Framework
- **Window System** - Windows with title bars and close buttons
- **Button Widget** - Clickable buttons with hover and pressed states
- **Textbox Widget** - Text input with cursor and password mode
- **Label Widget** - Static text display with custom colors

#### User Interface
- **Login Screen** - Graphical authentication system
  - Username and password fields
  - Tab navigation between fields
  - Password masking (asterisks)
  - Error messages for invalid credentials
  - Default credentials: admin/password
- **Desktop Environment** - Post-login graphical desktop
  - Welcome window with system information
  - Desktop icons (Terminal, Files, Settings)
  - Taskbar with clock
  - About and Shutdown buttons

#### Input System
- **Keyboard Mode Routing** - Support for shell, login, and desktop modes
- **GUI Input Handling** - Tab navigation, Enter to submit, Backspace support
- **Focus Management** - Visual indication of focused widgets

### Changed

#### Core System
- **Kernel Boot** - Now supports GUI mode (default) and text mode
- **Keyboard Driver** - Enhanced to route input based on current mode
- **Memory Management** - Added `strcpy()` function for string operations

#### Build System
- **Makefile** - Updated to include GUI source files
- **Project Structure** - Added `kernel/gui/` directory

### Documentation

#### New Documentation
- `docs/GUI_SYSTEM.md` - Complete GUI system guide
- `docs/SCREENSHOTS.md` - Screenshot and display information
- `docs/CI_TROUBLESHOOTING.md` - CI/CD troubleshooting guide
- `CHANGELOG.md` - This file

#### Updated Documentation
- `README.md` - Added GUI features and quick start
- `docs/QUICK_START.md` - Updated with GUI instructions

### Technical Details

#### Files Added
```
include/
├── vga.h          # VGA graphics interface
├── font.h         # Font rendering interface
├── gui.h          # GUI framework interface
├── login.h        # Login screen interface
└── desktop.h      # Desktop environment interface

kernel/drivers/
├── vga.c          # VGA Mode 13h implementation
└── font.c         # 8x8 bitmap font renderer

kernel/gui/
├── gui.c          # GUI widgets implementation
├── login.c        # Login screen implementation
└── desktop.c      # Desktop environment implementation
```

#### Lines of Code
- **Total Added**: ~1,850 lines
- **VGA Driver**: ~150 lines
- **Font System**: ~200 lines
- **GUI Framework**: ~150 lines
- **Login System**: ~200 lines
- **Desktop**: ~150 lines
- **Documentation**: ~1,000 lines

---

## [0.1.0] - 2026-01-02

### Added - Initial Release

#### Bootloader
- **16-bit Real Mode Bootloader** - Custom bootloader in x86 assembly
- **Kernel Loading** - Loads kernel from disk into memory
- **Protected Mode Switch** - Transitions from 16-bit to 32-bit mode

#### Kernel
- **32-bit Protected Mode Kernel** - Main kernel in C
- **Kernel Entry Point** - Assembly entry point for kernel
- **Initialization** - System component initialization

#### CPU Management
- **GDT (Global Descriptor Table)** - Memory segmentation setup
- **IDT (Interrupt Descriptor Table)** - Interrupt handling setup
- **ISR (Interrupt Service Routines)** - Hardware interrupt handlers

#### Drivers
- **VGA Text Mode Driver** - 80x25 character display
- **PS/2 Keyboard Driver** - Keyboard input with IRQ1
- **Port I/O** - Low-level port communication

#### Memory Management
- **Basic Allocator** - Simple `kmalloc()` implementation
- **Page Alignment** - Page-aligned memory allocation
- **String Functions** - `memcpy()`, `memset()`, `strlen()`, `strcmp()`

#### Shell
- **Command-Line Interface** - Interactive shell
- **Built-in Commands**:
  - `help` - Show available commands
  - `clear` - Clear screen
  - `echo` - Print text
  - `version` - Show OS version
  - `about` - System information

#### Build System
- **Makefile** - Complete build automation
- **Cross-Compiler Support** - i686-elf-gcc toolchain
- **QEMU Integration** - Easy testing with `make run`

#### CI/CD
- **GitHub Actions** - Automated build on push
- **Release Workflow** - Automated releases on tags
- **Artifact Upload** - Build artifacts available for download

#### Documentation
- `README.md` - Project overview
- `docs/BUILDING.md` - Build instructions
- `docs/ARCHITECTURE.md` - System architecture
- `docs/BOOTLOADER.md` - Bootloader explanation
- `docs/KERNEL.md` - Kernel development guide
- `docs/MEMORY.md` - Memory management guide
- `docs/DRIVERS.md` - Driver development guide
- `docs/QUICK_START.md` - Quick start guide
- `docs/CI_CD.md` - CI/CD documentation
- `docs/CONTRIBUTING.md` - Contribution guidelines

---

## Version History Summary

| Version | Date | Description |
|---------|------|-------------|
| 0.2.0 | 2026-01-03 | GUI system with login and desktop |
| 0.1.0 | 2026-01-02 | Initial release with text mode |

---

## Upgrade Guide

### From 0.1.0 to 0.2.0

**No breaking changes!** The text mode shell is still available.

**To use GUI mode (default):**
```bash
git pull
make clean && make
make run
# Login with admin/password
```

**To use text mode:**
1. Edit `kernel/kernel.c`
2. Change `boot_mode = BOOT_MODE_GUI` to `boot_mode = BOOT_MODE_TEXT`
3. Rebuild: `make clean && make`
4. Run: `make run`

---

## Future Roadmap

### Version 0.3.0 (Planned)
- [ ] Mouse driver (PS/2 mouse support)
- [ ] Window dragging and resizing
- [ ] File browser GUI
- [ ] Terminal emulator in GUI
- [ ] Settings panel

### Version 0.4.0 (Planned)
- [ ] Multi-tasking support
- [ ] Process management
- [ ] Virtual memory
- [ ] File system (FAT12/16)

### Version 1.0.0 (Future)
- [ ] Network stack
- [ ] USB support
- [ ] Sound driver
- [ ] Multi-core support

---

## Contributors

- **Jyot Bhavsar** - Initial work and GUI system

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.

