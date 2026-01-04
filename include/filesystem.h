/**
 * filesystem.h - Simple in-memory file system
 * Provides basic file operations
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "types.h"

#define MAX_FILES 32
#define MAX_FILENAME 32
#define MAX_FILE_SIZE 1024

/**
 * File structure
 */
typedef struct {
    char name[MAX_FILENAME];
    char content[MAX_FILE_SIZE];
    uint32_t size;
    bool in_use;
} file_t;

/**
 * fs_init - Initialize the file system
 */
void fs_init(void);

/**
 * fs_create - Create a new file
 * @filename: Name of the file to create
 *
 * Return: 0 on success, -1 on error
 */
int fs_create(const char *filename);

/**
 * fs_write - Write content to a file
 * @filename: Name of the file
 * @content: Content to write
 *
 * Return: 0 on success, -1 on error
 */
int fs_write(const char *filename, const char *content);

/**
 * fs_read - Read content from a file
 * @filename: Name of the file
 * @buffer: Buffer to store content
 * @size: Size of buffer
 *
 * Return: Number of bytes read, -1 on error
 */
int fs_read(const char *filename, char *buffer, uint32_t size);

/**
 * fs_delete - Delete a file
 * @filename: Name of the file to delete
 *
 * Return: 0 on success, -1 on error
 */
int fs_delete(const char *filename);

/**
 * fs_list - List all files
 */
void fs_list(void);

/**
 * fs_exists - Check if a file exists
 * @filename: Name of the file
 *
 * Return: true if file exists, false otherwise
 */
bool fs_exists(const char *filename);

#endif // FILESYSTEM_H

