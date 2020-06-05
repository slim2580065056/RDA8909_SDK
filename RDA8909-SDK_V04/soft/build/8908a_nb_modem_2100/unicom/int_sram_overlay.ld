        .sys_sram_overlay_0
         {
             #if (USE_BINUTILS_2_19 == 1) 
             /* FIXME: LD 2.19 doesn't like empty overlays... */
             LONG(0)
             #endif 
             . = ALIGN(0x10);
         }

         .sys_sram_overlay_1
         {
             #if (USE_BINUTILS_2_19 == 1) 
             /* FIXME: LD 2.19 doesn't like empty overlays... */
             LONG(0)
             #endif 
             . = ALIGN(0x10);
         }

         .sys_sram_overlay_2
         {
             #if (USE_BINUTILS_2_19 == 1) 
             /* FIXME: LD 2.19 doesn't like empty overlays... */
             LONG(0)
             #endif 
             . = ALIGN(0x10);
         }

         .sys_sram_overlay_3
         {
             #if (USE_BINUTILS_2_19 == 1) 
             /* FIXME: LD 2.19 doesn't like empty overlays... */
             LONG(0)
             #endif 
             . = ALIGN(0x10);
         }

         .sys_sram_overlay_4
         {
             #if (USE_BINUTILS_2_19 == 1) 
             /* FIXME: LD 2.19 doesn't like empty overlays... */
             LONG(0)
             #endif 
             . = ALIGN(0x10);
         }

         .sys_sram_overlay_5
         {
             #if (USE_BINUTILS_2_19 == 1) 
             /* FIXME: LD 2.19 doesn't like empty overlays... */
             LONG(0)
             #endif 
             . = ALIGN(0x10);
         }

         #define FLASH_SIZE_OF_SYS_SRAM_OVERLAY 0 + SIZEOF(.sys_sram_overlay_0) + SIZEOF(.sys_sram_overlay_1) + SIZEOF(.sys_sram_overlay_2) + SIZEOF(.sys_sram_overlay_3) + SIZEOF(.sys_sram_overlay_4) + SIZEOF(.sys_sram_overlay_5)
         #define MAX_SIZE_OF_SYS_SRAM_OVERLAY MAX(SIZEOF(.sys_sram_overlay_5), MAX(SIZEOF(.sys_sram_overlay_4), MAX(SIZEOF(.sys_sram_overlay_3), MAX(SIZEOF(.sys_sram_overlay_2), MAX(SIZEOF(.sys_sram_overlay_1), MAX(SIZEOF(.sys_sram_overlay_0), 0))))))

