/**
 * types.h - Standard type definitions for SimpleOS
 */

#ifndef TYPES_H
#define TYPES_H

// Unsigned integer types
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

// Signed integer types
typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;

// Size type
typedef uint32_t size_t;

// Boolean type
typedef enum {
    false = 0,
    true = 1
} bool;

// NULL pointer
#define NULL ((void*)0)

#endif // TYPES_H

