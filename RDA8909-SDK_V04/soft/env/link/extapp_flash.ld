/* Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
 * All rights reserved.
 *
 * This software is supplied "AS IS" without any warranties.
 * RDA assumes no responsibility or liability for the use of the software,
 * conveys no license or title under any patent, copyright, or mask work
 * right to the product. RDA reserves the right to make changes in the
 * software without notification.  RDA also make no representation or
 * warranty that such application will be suitable for the specified use
 * without further testing or modification.
 */

/* external application on flash link script */

#undef mips
#define mips mips
OUTPUT_ARCH(mips)
ENTRY(app_enter)
EXTERN(app_enter)
EXTERN(app_exit)

#define ROTEXT() .text .text.* .gnu.linkonce.t.*
#define RODATA() .rdata .rodata .rodata.* .gnu.linkonce.r.*
#define DATA() .data .data.* .gnu.linkonce.d.*
#define BSS() .bss .bss.* COMMON .scommon .sbss .sbss.* .sbss2 .sbss2.* .gnu.linkonce.b.*

#define MEM_CACHED_UNCACHED_OFFSET 0x20000000
#define RAM_RESERVED_SIZE (RAM_EXTAPP_SIZE + RAM_BTFW_SIZE)

MEMORY {
    flash (rx): ORIGIN = CODE_FLASH_PHY_END, LENGTH = FLASH_EXTAPP_SIZE
    ram (rwx): ORIGIN = EXT_RAM_BASE + RAM_SIZE - RAM_RESERVED_SIZE, LENGTH = RAM_EXTAPP_SIZE
}

SECTIONS {
    . = ORIGIN(flash);
    __flash_start = .;

    .appheader : {
        LONG(0x41505031)
        LONG(app_enter)
        LONG(app_exit)
        LONG(0)

        LONG(2)
        LONG(__sdkstub_load_start - __flash_start)
        LONG(__sdkstub_end - __sdkstub_start)
        LONG(__sdkstub_start)

        LONG(1)
        LONG(__data_load_start - __flash_start)
        LONG(__data_end - __data_start)
        LONG(__data_start)

        LONG(1)
        LONG(__ucdata_load_start - __flash_start)
        LONG(__ucdata_end - __ucdata_start)
        LONG(__ucdata_start)

        LONG(3)
        LONG(0)
        LONG(__bss_end - __bss_start)
        LONG(__bss_start)

        LONG(3)
        LONG(0)
        LONG(__ucbss_end - __ucbss_start)
        LONG(__ucbss_start)

        LONG(0)
        LONG(0)
        LONG(0)
        LONG(0)

        LONG(0)
        LONG(0)
        LONG(0)
        LONG(0)
    } > flash

    .text ALIGN(0x10) : {
        __text_start = .;
        *(ROTEXT() RODATA())
        __text_end = .;
    } > flash

    __text_load_start = LOADADDR(.text);

    . = ORIGIN(ram);
    __ram_start = .;

    .sdkstub ALIGN(0x10) : {
        __sdkstub_start = .;
        *(.sdkstub.*)
        __sdkstub_end = .;
    } AT>flash

    __sdkstub_load_start = LOADADDR(.sdkstub);

    .data ALIGN(0x10) : {
        __data_start = .;
        *(DATA())
        __data_end = .;
    } AT>flash

    __data_load_start = LOADADDR(.data);

    . += MEM_CACHED_UNCACHED_OFFSET;
    .ucdata ALIGN(0x10) : {
        __ucdata_start = .;
        *(.ucdata)
        __ucdata_end = .;
    } AT>flash
    . -= MEM_CACHED_UNCACHED_OFFSET;

    __ucdata_load_start = LOADADDR(.ucdata);
    __flash_end = LOADADDR(.ucdata) + SIZEOF(.ucdata);

    .bss ALIGN(0x10) : {
        __bss_start = .;
        *(BSS())
        __bss_end = .;
    }

    . += MEM_CACHED_UNCACHED_OFFSET;
    .ucbss ALIGN(0x10) : {
        __ucbss_start = .;
        *(.ucbss)
        __ucbss_end = .;
    }
    . -= MEM_CACHED_UNCACHED_OFFSET;

    __ram_end = .;

    ASSERT(__flash_end <= ORIGIN(flash) + LENGTH(flash), "FLASH overflow")
    ASSERT(__ram_end <= ORIGIN(ram) + LENGTH(ram), "RAM overflow")

    /DISCARD/ : {
        *(.MIPS.abiflags)
        *(.rel.dyn)
    }
}
