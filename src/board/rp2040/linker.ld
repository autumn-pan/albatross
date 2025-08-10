{
  FLASH (rx)  : ORIGIN = 0x10000000, LENGTH = 2M     /* External QSPI flash */
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 256K   /* SRAM (RP2040 has 264K, but 256K is safe default) */
}

initial_sp = ORIGIN(RAM) + LENGTH(RAM);



SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    *(.text*)
    *(.rodata*)
    KEEP(*(.init))
    KEEP(*(.fini))
  } > FLASH

  .data : AT(LOADADDR(.data))
  {
    _start_idata = LOADADDR(.data);
    _start_data = .;
    *(.data*)
    _end_data = .;
  } > RAM

  .bss :
  {
    _start_bss = .;
    *(.bss*)
    *(COMMON)
    _end_bss = .;
  } > RAM
}