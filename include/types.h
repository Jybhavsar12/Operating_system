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

// Boolean type - use standard definitions to avoid C23 keyword conflicts
#ifndef __cplusplus
#define bool  _Bool
#define true  1
#define false 0
#endif

// NULL pointer
#define NULL ((void*)0)

#endif // TYPES_H

