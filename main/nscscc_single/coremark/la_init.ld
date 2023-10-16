ENTRY(_init)

PROVIDE(SerialData = 0xBFD003F8);
PROVIDE(SerialStat = 0xBFD003FC);

PROVIDE(KERNEL_STACK_INIT = 0x80800000);

SECTIONS
{
    .text : {*(.init) *(.text)}
}
