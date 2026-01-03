# Contributing to SimpleOS

## Welcome

Thank you for your interest in contributing to SimpleOS! This document provides guidelines and instructions for contributing to the project.

## Code of Conduct

### Our Standards

- Be respectful and inclusive
- Welcome newcomers and help them learn
- Focus on constructive criticism
- Prioritize education and clarity over optimization
- Document your code thoroughly

### Unacceptable Behavior

- Harassment or discriminatory language
- Trolling or insulting comments
- Publishing others' private information
- Other conduct inappropriate in a professional setting

## How to Contribute

### Reporting Bugs

Before creating a bug report:
1. Check the existing issues to avoid duplicates
2. Test with the latest version
3. Verify the issue is reproducible

When creating a bug report, include:
- OS version and commit hash
- Steps to reproduce
- Expected vs actual behavior
- Screenshots or error messages
- Your environment (host OS, QEMU version, etc.)

### Suggesting Enhancements

Enhancement suggestions are welcome! Please:
- Use a clear and descriptive title
- Provide detailed description of the proposed feature
- Explain why this enhancement would be useful
- Consider educational value for learners

### Pull Requests

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly
5. Commit with clear messages
6. Push to your fork
7. Open a Pull Request

## Development Guidelines

### Code Style

#### C Code

```c
// Use descriptive variable names
int screen_row = 0;  // Good
int sr = 0;          // Bad

// Function naming: lowercase with underscores
void init_screen() {
    // Implementation
}

// Constants: uppercase with underscores
#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25

// Struct naming: lowercase with underscores
struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    // ...
};

// Always use braces for control structures
if (condition) {
    do_something();
} else {
    do_something_else();
}

// Comment complex logic
// Calculate VGA buffer offset: (row * 80 + col) * 2
int offset = get_screen_offset(row, col);
```

#### Assembly Code

```asm
; Use comments to explain what code does
; Labels should be descriptive
load_kernel:
    mov ah, 0x02        ; BIOS read sector function
    mov al, 15          ; Number of sectors to read
    ; ... more code

; Align data properly
align 4
gdt_start:
    dd 0x0
    dd 0x0
```

### Documentation

Every function must have a comment explaining:
- Purpose
- Parameters
- Return value
- Side effects (if any)

Example:
```c
/**
 * print_char - Print a single character to screen
 * @c: Character to print
 * @col: Column position (0-79)
 * @row: Row position (0-24)
 * @attr: Character attribute (color)
 *
 * Writes a character directly to VGA text buffer.
 * Automatically handles scrolling if row >= MAX_ROWS.
 */
void print_char(char c, int col, int row, char attr) {
    // Implementation
}
```

### Commit Messages

Follow this format:
```
<component>: <short description>

<detailed description if needed>

<issue reference if applicable>
```

Examples:
```
bootloader: Add error handling for disk read failures

Added check for BIOS disk read errors and display
error message if kernel cannot be loaded.

Fixes #42
```

```
screen: Implement scrolling functionality

- Added scroll_screen() function
- Updated print_char() to call scroll when needed
- Tested with long output
```

### Testing

Before submitting:
1. Build the OS successfully
2. Test in QEMU
3. Verify no regressions in existing features
4. Test edge cases
5. Update documentation if needed

### Areas for Contribution

#### Beginner-Friendly

- Documentation improvements
- Code comments
- Bug fixes
- Test cases
- Examples and tutorials

#### Intermediate

- New device drivers
- Shell commands
- Memory management improvements
- Error handling

#### Advanced

- File system implementation
- Process scheduling
- Virtual memory
- Network stack

## Project Structure

```
Operating_system/
├── boot/           # Bootloader code
├── kernel/         # Kernel source
│   ├── cpu/       # CPU management (GDT, IDT, ISR)
│   ├── drivers/   # Device drivers
│   └── memory/    # Memory management
├── include/       # Header files
├── docs/          # Documentation
└── build/         # Build output (generated)
```

## Getting Help

- Read the documentation in docs/
- Check existing issues and pull requests
- Ask questions in issue discussions
- Reference the OSDev wiki for OS development concepts

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

## Recognition

Contributors will be acknowledged in the project README and release notes.

Thank you for contributing to SimpleOS!

