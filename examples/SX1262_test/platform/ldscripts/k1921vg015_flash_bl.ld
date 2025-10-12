/** @file
*  @brief linker script for K1921VG015: project in Flash with UART BootLoader (Flasher)
          UART BootLoader must be preloaded in flash (ROM_BL)
*/

OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY {
  ROM_BL (rwx) : ORIGIN = 0x80000000, LENGTH = 8K
  ROM  (rwx) : ORIGIN = 0x80002000, LENGTH = 1016K
  RAM0 (rwx) : ORIGIN = 0x40000000, LENGTH = 256K
  RAM1 (rwx) : ORIGIN = 0x10000000, LENGTH = 64K
}

REGION_ALIAS("REGION_TEXT",   ROM );
REGION_ALIAS("REGION_RODATA", ROM );
REGION_ALIAS("REGION_DATA",   RAM0);
REGION_ALIAS("REGION_BSS",    RAM0);
REGION_ALIAS("REGION_STACK",  RAM0);

STACK_SIZE = 2048;

INCLUDE "k1921vg015_common.lds"
