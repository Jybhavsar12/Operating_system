/**
 * memory.h - Memory management interface
 */

#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

/**
 * kmalloc - Allocate kernel memory
 * @size: Number of bytes to allocate
 *
 * Return: Pointer to allocated memory
 */
void *kmalloc(uint32_t size);

/**
 * kmalloc_aligned - Allocate page-aligned kernel memory
 * @size: Number of bytes to allocate
 *
 * Return: Pointer to allocated memory (page-aligned)
 */
void *kmalloc_aligned(uint32_t size);

/**
 * kfree - Free kernel memory
 * @ptr: Pointer to memory to free
 */
void kfree(void *ptr);

/**
 * memcpy - Copy memory from source to destination
 * @dest: Destination address
 * @src: Source address
 * @n: Number of bytes to copy
 *
 * Return: Pointer to destination
 */
void *memcpy(void *dest, const void *src, uint32_t n);

/**
 * memset - Fill memory with a constant byte
 * @dest: Destination address
 * @val: Value to set
 * @n: Number of bytes to set
 *
 * Return: Pointer to destination
 */
void *memset(void *dest, uint8_t val, uint32_t n);

/**
 * strlen - Calculate length of string
 * @str: Null-terminated string
 *
 * Return: Length of string (excluding null terminator)
 */
uint32_t strlen(const char *str);

/**
 * strcmp - Compare two strings
 * @str1: First string
 * @str2: Second string
 *
 * Return: 0 if equal, negative if str1 < str2, positive if str1 > str2
 */
int strcmp(const char *str1, const char *str2);

#endif // MEMORY_H

