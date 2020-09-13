#include <stddef.h>
#include <stdbool.h>
#include <stdarg.h>
#include <lib/print.h>
#include <lib/module.h>
#include <lib/asm.h>
#include <lib/blib.h>
#include <lib/gdt.h>

#define MAX_MODULES 16

static struct module modules[MAX_MODULES];
static size_t modules_i = 0;

void init_module(struct module *m) {
    if (modules_i >= MAX_MODULES)
        panic("Trying too load more than MAX_MODULES modules.\n");

    struct module_header *h = m->ptr;
    call_to_module((struct module *)h->start, NULL, modules_i);

    modules[modules_i++] = *m;
}

void init_modules(size_t count, struct module_header *modules) {
    for (size_t i = 0; i < count; i++) {
        struct module m = {
            (void *)modules,
            modules->size
        };
        init_module(&m);
        modules = (void *)((size_t)modules + modules->size);
    }
}

void *call_to_module(struct module *m, void *ptr, ...) {
    va_list args;
    va_start(args, ptr);

    gdt_set_descriptor(7, (size_t)m->ptr, m->size / 4096);
    gdt_set_descriptor(8, (size_t)m->ptr, m->size / 4096);

    void *ret;

    ASM(
        "pusha\n\t"

        "mov dx, 0x40\n\t"
        "mov ds, dx\n\t"
        "mov es, dx\n\t"
        "mov fs, dx\n\t"
        "mov gs, dx\n\t"

        // iret frame from trampoline
        "mov edx, esp\n\t"
        "push 0x20\n\t"
        "push edx\n\t"
        "push 0x2\n\t"
        "push 0x18\n\t"
        "push 1f\n\t"

        // iret frame to trampoline
        "push 0x40\n\t"
        "push 0\n\t"
        "push 0x2\n\t"
        "push 0x38\n\t"
        "push 0\n\t"
        "iret\n\t"

        "1:\n\t"
        "mov %0, eax\n\t"

        "popa\n\t"
        , "=c"(ret)
        : "a"(args), "b"(ptr)
        : "memory"
    );

    va_end(args);

    return ret;
}
