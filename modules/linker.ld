OUTPUT_FORMAT(binary)
ENTRY(main)

SECTIONS
{
    . = 0;

    .text : {
        *(.text.trampoline)
        *(.text*)
    }

    .rodata : {
        *(.rodata*)
    }

    .data : {
        *(.data*)
        *(COMMON)
        *(.bss*)
    }
}
