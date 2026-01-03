/**
 * ports.h - Port I/O functions for hardware communication
 */

#ifndef PORTS_H
#define PORTS_H

#include "types.h"

/**
 * port_byte_in - Read a byte from a port
 * @port: Port number
 *
 * Return: Byte read from port
 */
uint8_t port_byte_in(uint16_t port);

/**
 * port_byte_out - Write a byte to a port
 * @port: Port number
 * @data: Byte to write
 */
void port_byte_out(uint16_t port, uint8_t data);

/**
 * port_word_in - Read a word from a port
 * @port: Port number
 *
 * Return: Word read from port
 */
uint16_t port_word_in(uint16_t port);

/**
 * port_word_out - Write a word to a port
 * @port: Port number
 * @data: Word to write
 */
void port_word_out(uint16_t port, uint16_t data);

#endif // PORTS_H

