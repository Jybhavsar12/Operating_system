/**
 * filesystem.c - Simple in-memory file system
 * Provides basic file operations
 */

#include "../../include/filesystem.h"
#include "../../include/memory.h"
#include "../../include/screen.h"

// File system storage
static file_t files[MAX_FILES];

/**
 * fs_init - Initialize the file system
 */
void fs_init(void) {
    for (int i = 0; i < MAX_FILES; i++) {
        files[i].in_use = false;
        files[i].name[0] = '\0';
        files[i].size = 0;
    }
}

/**
 * fs_find - Find a file by name
 * @filename: Name of the file
 *
 * Return: Index of file, -1 if not found
 */
static int fs_find(const char *filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].in_use && strcmp(files[i].name, filename) == 0) {
            return i;
        }
    }
    return -1;
}

/**
 * fs_create - Create a new file
 * @filename: Name of the file to create
 *
 * Return: 0 on success, -1 on error
 */
int fs_create(const char *filename) {
    // Check if file already exists
    if (fs_find(filename) != -1) {
        return -1; // File already exists
    }
    
    // Check filename length
    if (strlen(filename) >= MAX_FILENAME) {
        return -1; // Filename too long
    }
    
    // Find empty slot
    for (int i = 0; i < MAX_FILES; i++) {
        if (!files[i].in_use) {
            files[i].in_use = true;
            strcpy(files[i].name, filename);
            files[i].size = 0;
            files[i].content[0] = '\0';
            return 0;
        }
    }
    
    return -1; // No space available
}

/**
 * fs_write - Write content to a file
 * @filename: Name of the file
 * @content: Content to write
 *
 * Return: 0 on success, -1 on error
 */
int fs_write(const char *filename, const char *content) {
    int idx = fs_find(filename);
    if (idx == -1) {
        return -1; // File not found
    }
    
    uint32_t len = strlen(content);
    if (len >= MAX_FILE_SIZE) {
        len = MAX_FILE_SIZE - 1;
    }
    
    // Copy content
    for (uint32_t i = 0; i < len; i++) {
        files[idx].content[i] = content[i];
    }
    files[idx].content[len] = '\0';
    files[idx].size = len;
    
    return 0;
}

/**
 * fs_read - Read content from a file
 * @filename: Name of the file
 * @buffer: Buffer to store content
 * @size: Size of buffer
 *
 * Return: Number of bytes read, -1 on error
 */
int fs_read(const char *filename, char *buffer, uint32_t size) {
    int idx = fs_find(filename);
    if (idx == -1) {
        return -1; // File not found
    }
    
    uint32_t len = files[idx].size;
    if (len >= size) {
        len = size - 1;
    }
    
    // Copy content
    for (uint32_t i = 0; i < len; i++) {
        buffer[i] = files[idx].content[i];
    }
    buffer[len] = '\0';
    
    return len;
}

/**
 * fs_delete - Delete a file
 * @filename: Name of the file to delete
 *
 * Return: 0 on success, -1 on error
 */
int fs_delete(const char *filename) {
    int idx = fs_find(filename);
    if (idx == -1) {
        return -1; // File not found
    }
    
    files[idx].in_use = false;
    files[idx].name[0] = '\0';
    files[idx].size = 0;
    
    return 0;
}

/**
 * fs_list - List all files
 */
void fs_list(void) {
    int count = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].in_use) {
            count++;
        }
    }
    
    if (count == 0) {
        print("No files found.\n");
        return;
    }
    
    print("Files:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (files[i].in_use) {
            print("  ");
            print(files[i].name);
            print(" (");
            print_int(files[i].size);
            print(" bytes)\n");
        }
    }
}

/**
 * fs_exists - Check if a file exists
 * @filename: Name of the file
 *
 * Return: true if file exists, false otherwise
 */
bool fs_exists(const char *filename) {
    return fs_find(filename) != -1;
}

