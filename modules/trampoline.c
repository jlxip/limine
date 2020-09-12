__attribute__((naked))
void trampoline(void) {
    // EAX = va_args
    // EBX = routine address (0 if main routine)
    // ECX = return instruction pointer
    // EDX = return stack pointer
    "mov esp, OFFSET stack\n\t"
    "test ebx, ebx\n\t"
    "jnz 1f\n\t"
    "mov ebx, OFFSET main\n\t"
    "1:\n\t"
    "push eax\n\t"
    "call ebx\n\t"
    "iret\n\t"
}
