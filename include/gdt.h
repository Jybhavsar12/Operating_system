/**
 * gdt.h - Global Descriptor Table interface
 */

#ifndef GDT_H
#define GDT_H

#include "types.h"

/**
 * gdt_init - Initialize the Global Descriptor Table
 */
void gdt_init(void);

#endif // GDT_H

