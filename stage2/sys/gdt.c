#include <stddef.h>
#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

void gdt_set_descriptor(int entry, size_t base, size_t page_count) {
    struct {
        uint16_t size;
        struct gdt_entry *ptr;
    } __attribute__((packed)) gdt;

    asm volatile (
        "sgdt %0\n\t"
        : "=m"(gdt)
        :
        : "memory"
    );

    gdt.ptr[entry].base_low = (uint16_t)(base & 0x0000ffff);
    gdt.ptr[entry].base_mid = (uint8_t)((base & 0x00ff0000) / 0x10000);
    gdt.ptr[entry].base_high = (uint8_t)((base & 0xff000000) / 0x1000000);

    gdt.ptr[entry].limit_low = (uint16_t)((page_count - 1) & 0x0000ffff);
    gdt.ptr[entry].granularity = (uint8_t)((gdt.ptr[entry].granularity & 0xf0) | ((page_count & 0x000f0000) / 0x10000));
}
