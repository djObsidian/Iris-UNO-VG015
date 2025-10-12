/// @file
/// @brief platform init funcs

#include <sys/errno.h>
#include <string.h>
#include <unistd.h>

#include "memasm.h"

extern char _tdata_start[], _tdata_end[], _tbss_start[], _tbss_end[];

extern const uint8_t __data_source_start;
extern uint8_t __data_target_start;
extern uint8_t __data_target_end;

extern const uint8_t __sdata_source_start;
extern uint8_t __sdata_target_start;
extern uint8_t __sdata_target_end;

extern const uint8_t __init_array_source_start;
extern uint8_t __init_array_target_start;
extern uint8_t __init_array_target_end;

extern const uint8_t __fini_array_source_start;
extern uint8_t __fini_array_target_start;
extern uint8_t __fini_array_target_end;

extern void plf_init_relocate(void) __attribute__((weak));

extern char __bss_start[], __bss_end[];

void __init plf_init_noreloc(void)
{
    // do nothing
}

void __init plf_init_generic(void)
{
    // init BSS
    memset(__bss_start, 0, (size_t)(__bss_end - __bss_start));

    memcpy((void*)&__data_target_start,
           (const void*)&__data_source_start,
           (&__data_target_end - &__data_target_start));

    memcpy((void*)&__sdata_target_start,
              (const void*)&__sdata_source_start,
              (&__sdata_target_end - &__sdata_target_start));

    memcpy((void*)&__init_array_target_start,
              (const void*)&__init_array_source_start,
              (&__init_array_target_end - &__init_array_target_start));

    memcpy((void*)&__fini_array_target_start,
              (const void*)&__fini_array_source_start,
              (&__fini_array_target_end - &__fini_array_target_start));

    // init functions for cpp
    for (uint32_t i = 0; i < ((uint32_t) (&__init_array_target_end - &__init_array_target_start)) >> 2; i++)
    	((void (*)())((uint32_t*)&__init_array_target_start)[i])();
}

void plf_init(void) __attribute__((weak, alias("plf_init_generic")));

