ENTRY(_init)

PROVIDE(KERNEL_STACK_INIT = 0x80800000);

SECTIONS
{
    .text : {*(.init) *(.text)}
}
