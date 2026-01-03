/**
 * ports.c - Port I/O functions implementation
 * Low-level functions for reading/writing to hardware ports
 */

#include "../../include/ports.h"

/**
 * port_byte_in - Read a byte from a port
 * @port: Port number
 *
 * Return: Byte read from port
 */
uint8_t port_byte_in(uint16_t port) {
    uint8_t result;
    __asm__ __volatile__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

/**
 * port_byte_out - Write a byte to a port
 * @port: Port number
 * @data: Byte to write
 */
void port_byte_out(uint16_t port, uint8_t data) {
    __asm__ __volatile__("out %%al, %%dx" : : "a" (data), "d" (port));
}

/**
 * port_word_in - Read a word from a port
 * @port: Port number
 *
 * Return: Word read from port
 */
uint16_t port_word_in(uint16_t port) {
    uint16_t result;
    __asm__ __volatile__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

/**
 * port_word_out - Write a word to a port
 * @port: Port number
 * @data: Word to write
 */
void port_word_out(uint16_t port, uint16_t data) {
    __asm__ __volatile__("out %%ax, %%dx" : : "a" (data), "d" (port));
}

