.section .init
.global _init

_init:
    la.global   $r3, KERNEL_STACK_INIT
    b           main
