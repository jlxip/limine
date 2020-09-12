#ifndef __LIB__MODULE_H__
#define __LIB__MODULE_H__

#include <stddef.h>
#include <stdint.h>

struct module {
    void  *ptr;
    size_t size;
};

struct module_header {
    size_t size;
    size_t padding[3];
    void *start[];
};

void init_module(struct module *m);
void init_modules(size_t count, struct module_header *modules);
void *call_to_module(struct module *m, void *ptr, ...);

#endif
