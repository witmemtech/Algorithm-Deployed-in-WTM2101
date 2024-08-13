/*
 *  Version: 2.0.0, 2022.02.15
 *      rewrite link script
 *      1. stack in DLM
 *      2. others in ILM
 *      3. no move data
 *
 *  Version: 2.1.0, 2022.09.18
 *
 */
MEMORY
{
    /* useless for segger emstudio, but */
    UNPLACED_SECTIONS (wx)  : ORIGIN = 0x100000000, LENGTH = 0x00000000
    ILM (rx)                : ORIGIN =  0x00000000, LENGTH = 0x00028000
    DLM (wx)                : ORIGIN =  0x20000000, LENGTH = 0x00020000
    NPU (rw)                : ORIGIN =  0x30030000, LENGTH = 0x00008000
}

SECTIONS
{
    /*                                                      */
    /* CODE, 256K                                           */
    /*    0x0000_0000 - 0x0001_FFFF, RAM0, 128K (ilm only)  */
    /*    0x0002_0000 - 0x0002_7FFF, RAM4,  32K             */
    /*    0x0002_8000 - 0x0002_FFFF, RAM3,  32K             */
    /*    0x0003_0000 - 0x0003_FFFF, RAM2,  64K             */
    /*                                                      */
    /* DATA, 128K                                           */
    /*    0x2000_0000 - 0x2000_FFFF, RAM1,  64K (dlm only)  */
    /*    0x2001_0000 - 0x2001_FFFF, RAM2,  64K             */
    /*    0x2002_0000 - 0x2002_7FFF, RAM3,  32K             */
    /*    0x2002_8000 - 0x2002_FFFF, RAM4,  32K             */
    /*                                                      */
    /* SYS, 320K                                            */
    /*    0x3000_0000 - 0x3001_FFFF, RAM0, 128K             */
    /*    0x3002_0000 - 0x3002_FFFF, RAM1,  64K             */
    /*    0x3003_0000 - 0x3003_FFFF, RAM2,  64K             */
    /*    0x3004_0000 - 0x3004_7FFF, RAM3,  32K             */
    /*    0x3004_8000 - 0x3004_FFFF, RAM4,  32K             */

    /* ilm: 128K, dlm: 64K, sys: 128K */
    /*__ILM_segment_start__     = 0x00000000;*/ /* included */
    /*__ILM_segment_end__       = 0x00020000;*/ /* not included */
    /*__ILM_segment_size__      = 0x00020000;*/

    /*__DLM_segment_start__     = 0x20000000;*/ /* included */
    /*__DLM_segment_end__       = 0x20010000;*/ /* not included */
    /*__DLM_segment_size__      = 0x00010000;*/

    /*__RAM_segment_start__     = 0x30030000;*/ /* included */
    /*__RAM_segment_end__       = 0x30048000;*/ /* not included */
    /*__RAM_segment_size__      = 0x00018000;*/

    /*__NPU_segment_start__     = 0x30048000;*/ /* included */
    /*__NPU_segment_end__       = 0x30050000;*/ /* not included */
    /*__NPU_segment_size__      = 0x00008000;*/


    /* ILM: 160KB */
    /* RAM0 */
    /* RAM4 */
    __ILM_segment_start__     = 0x00000000; /* included */
    __ILM_segment_end__       = 0x00028000; /* not included */
    __ILM_segment_size__      = 0x00028000;

    /* DLM: 64KB */
    /* RAM1 */
    /* RAM2 */
    __DLM_segment_start__     = 0x20000000; /* included */
    __DLM_segment_end__       = 0x20020000; /* not included */
    __DLM_segment_size__      = 0x00020000;
    __DLM_actual_size__       = __DLM_segment_size__ - __HEAPSIZE__ - __STACKSIZE__;

    /* RAM3 */
    __DMA_segment_start__     = 0x20020000; /* included */
    __DMA_segment_end__       = 0x20028000; /* not included */
    __DMA_segment_size__      = 0x00008000;


    __HEAPSIZE__    = 0;
    __STACKSIZE__   = 1024 * 10;

    /*
     *  ILM:
     *      .vectors
     *      .init
     *      .text
     *      .rodata
     *      .data (store)
     *
     *  DLM:
     *      .audmem
     *      .bss
     *      .heap
     *      .stack
     *      .nnmem
     *
     */

    /*******************************************************************************/
    /* */
    /* ------ ILM below ------ */
    /* */
    /*  reset vector: fixed-placement */
    __vectors_load_start__      = ALIGN(__ILM_segment_start__, 4);
    __vectors_runtime_start__   = ALIGN(__ILM_segment_start__, 4);
    .vectors __vectors_runtime_start__ : AT(__vectors_load_start__)
    {
      __vectors_start__ = .;
      *(.vectors .vectors.*)
    }
    /* calculate (start,end,range) */
    __vectors_size__            = SIZEOF(.vectors);
    __vectors_end__             = __vectors_start__ + __vectors_size__;
    __vectors_load_end__        = __vectors_end__;


    /*******************************************************************************/
    __init_load_start__         = ALIGN(__vectors_end__ , 4);
    __init_runtime_start__      = ALIGN(__vectors_end__ , 4);
    .init __init_runtime_start__ : AT(__init_load_start__)
    {
      __init_start__ = .;
      *(.init .init.*)
    }
    __init_size__               = SIZEOF(.init);
    __init_end__                = __init_start__ + __init_size__;
    __init_load_end__           = __init_end__;


    /*******************************************************************************/
    __text_load_start__         = ALIGN(__init_end__ , 4);
    __text_runtime_start__      = ALIGN(__init_end__ , 4);
    .text __text_runtime_start__ : AT(__text_load_start__)
    {
      __text_start__ = .;
      *(.text .text.*)
    }
    __text_size__               = SIZEOF(.text);
    __text_end__                = __text_start__ + __text_size__;
    __text_load_end__           = __text_end__;

    . = ASSERT((__text_end__ - __ILM_segment_start__) < __ILM_segment_size__,
        "no room to place .text into ILM!!!");


    /*******************************************************************************/
    __dtors_load_start__        = ALIGN(__text_end__ , 4);
    __dtors_runtime_start__     = ALIGN(__text_end__ , 4);
    .dtors __dtors_runtime_start__ : AT(__dtors_load_start__)
    {
      __dtors_start__ = .;
      KEEP (*(SORT(.dtors.*)))
      KEEP (*(.dtors))
      KEEP (*(.fini_array))
      KEEP (*(SORT(.fini_array.*)))
    }
    __dtors_size__              = SIZEOF(.dtors);
    __dtors_end__               = __dtors_start__ + __dtors_size__;
    __dtors_load_end__          = __dtors_end__;


    /*******************************************************************************/
    __ctors_load_start__        = ALIGN(__dtors_end__ , 4);
    __ctors_runtime_start__     = ALIGN(__dtors_end__ , 4);
    .ctors __ctors_runtime_start__ : AT(__ctors_load_start__)
    {
      __ctors_start__ = .;
      KEEP (*(SORT(.ctors.*)))
      KEEP (*(.ctors))
      KEEP (*(.init_array))
      KEEP (*(SORT(.init_array.*)))
    }
    __ctors_size__              = SIZEOF(.ctors);
    __ctors_end__               = __ctors_start__ + __ctors_size__;
    __ctors_load_end__          = __ctors_end__;


    /*******************************************************************************/
    __rodata_load_start__       = ALIGN(__ctors_end__ , 4);
    __rodata_runtime_start__    = ALIGN(__ctors_end__ , 4);
    .rodata __rodata_runtime_start__ : AT(__rodata_load_start__)
    {
      __rodata_start__ = .;
      *(.rodata .rodata.*)
    }
    __rodata_size__             = SIZEOF(.rodata);
    __rodata_end__              = __rodata_start__ + __rodata_size__;
    __rodata_load_end__         = __rodata_end__;

    . = ASSERT((__rodata_end__ - __ILM_segment_start__) < __ILM_segment_size__,
        "no room to place .rodata into ILM!!!");


    /*******************************************************************************/
    __srodata_load_start__      = ALIGN(__rodata_end__ , 4);
    __srodata_runtime_start__   = ALIGN(__rodata_end__ , 4);
    .srodata __srodata_runtime_start__ : AT(__srodata_load_start__)
    {
      __srodata_start__ = .;
      *(.srodata .srodata.*)
    }
    __srodata_size__            = SIZEOF(.srodata);
    __srodata_end__             = __srodata_start__ + __srodata_size__;
    __srodata_load_end__        = __srodata_end__;

    . = ASSERT((__srodata_end__ - __ILM_segment_start__) < __ILM_segment_size__,
        "no room to place .srodata into ILM!!!");


    /*******************************************************************************/
    __data_load_start__         = ALIGN(__srodata_end__ , 4);
    __data_runtime_start__      = ALIGN(__srodata_end__, 4);

    .data __data_runtime_start__ : AT(__data_load_start__)
    {
      __data_start__ = .;
      *(.data .data.*)
    }
    __data_size__               = ALIGN(SIZEOF(.data), 4);
    __data_end__                = __data_start__      + __data_size__;
    __data_load_end__           = __data_load_start__ + __data_size__;

    . = ASSERT((__data_load_end__ - __ILM_segment_start__) < __ILM_segment_size__,
        "no room to place .data into ILM!!!");

    /*. = ASSERT((__data_end__ - __ILM_segment_start__) < __ILM_segment_size__,*/
    /*    "no room to place .data into ILM!!!");*/
    /*. = ASSERT((__data_end__ - __DLM_segment_start__) < __DLM_segment_size__,
        "no room to place .data into DLM!!!");*/


    /*******************************************************************************/
    /* .tdata */
    __tdata_load_start__        = ALIGN(__data_load_end__ , 4);
    __tdata_runtime_start__     = ALIGN(__data_end__ , 4);
    .tdata __tdata_runtime_start__ : AT(__tdata_load_start__)
    {
      __tdata_start__ = .;
      *(.tdata .tdata.*)
    }
    __tdata_size__              = ALIGN(SIZEOF(.tdata), 4);
    __tdata_end__               = __tdata_start__       + __tdata_size__;
    __tdata_load_end__          = __tdata_load_start__  + __tdata_size__;

    . = ASSERT((__tdata_load_end__ - __ILM_segment_start__) < __ILM_segment_size__,
        "no room to place .tdata into ILM!!!");

    /*. = ASSERT((__tdata_end__ - __RAM_segment_start__) < __RAM_segment_size__, */
    /*    "no room to place .tdata into RAM!!!");*/
    /*. = ASSERT((__tdata_end__ - __DLM_segment_start__) < __DLM_segment_size__,
        "no room to place .tdata into DLM!!!");*/


    /*******************************************************************************/
    /* .sdata */
    __sdata_load_start__        = ALIGN(__tdata_load_end__ , 4);
    __sdata_runtime_start__     = ALIGN(__tdata_end__ , 4);
    .sdata __sdata_runtime_start__ : AT(__sdata_load_start__)
    {
      __sdata_start__ = .;
      *(.sdata.* .sdata2.*)
    }
    __sdata_size__              = ALIGN(SIZEOF(.sdata), 4);
    __sdata_end__               = __sdata_start__       + __sdata_size__;
    __sdata_load_end__          = __sdata_load_start__  + __sdata_size__;

    . = ASSERT((__sdata_load_end__ - __ILM_segment_start__) < __ILM_segment_size__,
        "no room to place .sdata into ILM!!!");

    /*. = ASSERT((__sdata_end__ - __RAM_segment_start__) < __RAM_segment_size__,*/
    /*    "no room to place .sdata into RAM!!!");*/
    /*. = ASSERT((__sdata_end__ - __DLM_segment_start__) < __DLM_segment_size__,
        "no room to place .sdata into DLM!!!");*/



    /*******************************************************************************/
    /* */
    /* ------ DLM below ------ */
    /* */
    /* .bss and .heap .stack just runtime var, no need to store. */
    /* .bss */
    __bss_load_start__          = ALIGN(__DLM_segment_start__, 4);
    __bss_runtime_start__       = ALIGN(__DLM_segment_start__, 4);

    .bss __bss_runtime_start__ (NOLOAD) : AT(__bss_load_start__)
    {
      __bss_start__ = .;
      *(.bss .bss.*) *(COMMON)
    }
    __bss_size__                = ALIGN(SIZEOF(.bss), 4);
    __bss_end__                 = __bss_start__         + __bss_size__;
    __bss_load_end__            = __bss_load_start__    + __bss_size__;

    . = ASSERT((__bss_end__ - __DLM_segment_start__) < __DLM_actual_size__,
        "no room to place .bss into DLM!!!");


    /*******************************************************************************/
    /* .tbss */
    __tbss_load_start__         = ALIGN(__bss_load_end__, 4);
    __tbss_runtime_start__      = ALIGN(__bss_load_end__, 4);
    .tbss __tbss_runtime_start__ (NOLOAD) : AT(__tbss_load_start__)
    {
      __tbss_start__ = .;
      *(.tbss .tbss.*)
    }
    __tbss_size__               = ALIGN(SIZEOF(.tbss), 4);
    __tbss_end__                = __tbss_start__        + __tbss_size__;
    __tbss_load_end__           = __tbss_load_start__   + __tbss_size__;

    . = ASSERT((__tbss_end__ - __DLM_segment_start__) < __DLM_actual_size__,
        "no room to place .tbss into DLM!!!");


    /*******************************************************************************/
    /* .sbss */
    __sbss_load_start__         = ALIGN(__tbss_load_end__ , 4);
    __sbss_runtime_start__      = ALIGN(__tbss_load_end__ , 4);
    .sbss __sbss_runtime_start__ (NOLOAD) : AT(__sbss_load_start__)
    {
      __sbss_start__ = .;
      *(.sbss .sbss.*)
    }
    __sbss_size__               = ALIGN(SIZEOF(.sbss), 4);
    __sbss_end__                = __sbss_start__        + __sbss_size__;
    __sbss_load_end__           = __sbss_load_start__   + __sbss_size__;

    . = ASSERT((__sbss_end__ - __DLM_segment_start__) < __DLM_actual_size__,
        "no room to place .sbss int DLM!!!");


    /* misc */
    __non_init_load_start__     = ALIGN(__sbss_end__ , 4);
    __non_init_runtime_start__  = ALIGN(__sbss_end__ , 4);
    .non_init __non_init_runtime_start__ (NOLOAD) : AT(__non_init_load_start__)
    {
      __non_init_start__ = .;
      *(.non_init .non_init.*)
    }
    __non_init_size__           = SIZEOF(.non_init);
    __non_init_end__            = __non_init_start__ + __non_init_size__;
    __non_init_load_end__       = __non_init_end__;
    . = ASSERT((__non_init_end__ - __DLM_segment_start__) < __DLM_actual_size__,
        "no room to place .non_init int DLM!!!");


    __heap_load_start__         = ALIGN(__DLM_segment_end__ - __STACKSIZE__ - __HEAPSIZE__, 4);
    __heap_runtime_start__      = ALIGN(__DLM_segment_end__ - __STACKSIZE__ - __HEAPSIZE__, 4);
    .heap __heap_runtime_start__ (NOLOAD) : AT(__heap_load_start__)
    {
      __heap_start__ = .;
      *(.heap .heap.*)
      . = ALIGN(MAX(__heap_start__ + __HEAPSIZE__ , .), 4);
    }
    __heap_size__               = ALIGN(SIZEOF(.heap), 4);
    __heap_end__                = __heap_start__ + __heap_size__;
    __heap_load_end__           = __heap_end__;
    . = ASSERT((__heap_end__ - __DLM_segment_start__) < __DLM_segment_size__,
        "no room to place .heap!!!");


    __stack_load_start__        = ALIGN(__DLM_segment_end__ - __STACKSIZE__, 4);
    __stack_runtime_start__     = ALIGN(__DLM_segment_end__ - __STACKSIZE__, 4);
    .stack __stack_runtime_start__ (NOLOAD) : AT(__stack_load_start__)
    {
      __stack_start__ = .;
      *(.stack .stack.*)
      . = ALIGN(MAX(__stack_start__ + __STACKSIZE__ , .), 4);
    }
    __stack_size__              = ALIGN(SIZEOF(.stack), 4);
    __stack_end__               = __stack_start__ + __stack_size__;
    __stack_load_end__          = __stack_end__;
    . = ASSERT((__heap_size__ + __stack_size__) < __DLM_segment_size__,
        "no room to place .stack into RAM!!!");




    /*******************************************************************************/
    /* */
    /* ------ NPU below ------ */
    /* */
    __audmem_load_start__       = ALIGN(__DMA_segment_start__, 4);
    __audmem_runtime_start__    = ALIGN(__DMA_segment_start__, 4);
    .audmem __audmem_runtime_start__ (NOLOAD): AT(__audmem_load_start__)
    {
        __audmem_start__ = .;
        *(.audmem .audmem.*)
    }
    __audmem_size__             = ALIGN(SIZEOF(.audmem), 4);
    __audmem_end__              = __audmem_start__ + __audmem_size__;
    __audmem_load_end__         = __audmem_end__;
    . = ASSERT((__audmem_size__) < __DMA_segment_size__,
        "no room to place .stack into DMA!!!");




    /*******************************************************************************/
    /* this will show percent guage */
    __ILM_segment_used_end__  = 0;
    __ILM_segment_used_size__ = 0;

    __DLM_segment_used_end__  = 0;
    __DLM_segment_used_size__ = 0;

    __DMA_segment_used_end__  = 0;
    __DMA_segment_used_size__ = 0;
}
