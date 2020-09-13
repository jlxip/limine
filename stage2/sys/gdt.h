#ifndef __LIB__GDT_H__
#define __LIB__GDT_H__

#include <stddef.h>

void gdt_set_descriptor(int entry, size_t base, size_t page_count);

#endif
