/**
 * memory.c - Basic memory management
 * Simple heap allocator for kernel memory
 */

#include "../../include/memory.h"

// Simple memory allocator - just keeps track of next free address
static uint32_t free_mem_addr = 0x10000;  // Start after kernel

/**
 * kmalloc - Allocate kernel memory
 * @size: Number of bytes to allocate
 *
 * Return: Pointer to allocated memory
 */
void *kmalloc(uint32_t size) {
    void *addr = (void *)free_mem_addr;
    free_mem_addr += size;
    return addr;
}

/**
 * kmalloc_aligned - Allocate page-aligned kernel memory
 * @size: Number of bytes to allocate
 *
 * Return: Pointer to allocated memory (page-aligned)
 */
void *kmalloc_aligned(uint32_t size) {
    // Align to 4KB page boundary
    if (free_mem_addr & 0xFFF) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }
    void *addr = (void *)free_mem_addr;
    free_mem_addr += size;
    return addr;
}

/**
 * kfree - Free kernel memory
 * @ptr: Pointer to memory to free
 *
 * Note: This is a placeholder. A real implementation would
 * maintain a free list and reuse freed memory.
 */
void kfree(void *ptr) {
    // Simple allocator doesn't support freeing
    // In a real OS, this would add the block to a free list
}

/**
 * memcpy - Copy memory from source to destination
 * @dest: Destination address
 * @src: Source address
 * @n: Number of bytes to copy
 *
 * Return: Pointer to destination
 */
void *memcpy(void *dest, const void *src, uint32_t n) {
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;
    
    while (n--) {
        *d++ = *s++;
    }
    
    return dest;
}

/**
 * memset - Fill memory with a constant byte
 * @dest: Destination address
 * @val: Value to set
 * @n: Number of bytes to set
 *
 * Return: Pointer to destination
 */
void *memset(void *dest, uint8_t val, uint32_t n) {
    uint8_t *d = (uint8_t *)dest;
    
    while (n--) {
        *d++ = val;
    }
    
    return dest;
}

/**
 * strlen - Calculate length of string
 * @str: Null-terminated string
 *
 * Return: Length of string (excluding null terminator)
 */
uint32_t strlen(const char *str) {
    uint32_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

/**
 * strcmp - Compare two strings
 * @str1: First string
 * @str2: Second string
 *
 * Return: 0 if equal, negative if str1 < str2, positive if str1 > str2
 */
int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const uint8_t *)str1 - *(const uint8_t *)str2;
}

/**
 * strcpy - Copy string from source to destination
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to destination
 */
char *strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return original_dest;
}

