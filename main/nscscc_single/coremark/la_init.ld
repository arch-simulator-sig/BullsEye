ENTRY(_init)

PROVIDE(SerialData = 0xBFD003F8);
PROVIDE(SerialStat = 0xBFD003FC);
PROVIDE(CoreTicker = 0xBFD00400);

PROVIDE(KERNEL_STACK_INIT = 0x80800000);

SECTIONS
{
    .text : {*(.init) *(.text)}
}
