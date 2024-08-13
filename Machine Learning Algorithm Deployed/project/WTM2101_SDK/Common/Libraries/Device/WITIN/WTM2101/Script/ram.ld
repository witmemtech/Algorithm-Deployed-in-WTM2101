MEMORY
{
  UNPLACED_SECTIONS (wx) : ORIGIN = 0x100000000, LENGTH = 0
  RAM1 (wx) : ORIGIN = 0x00000000, LENGTH = 0x00040000
}

SECTIONS
{
  __RAM1_segment_start__ = 0x00000000;
  __RAM1_segment_end__ = 0x0003FFFF;
  __RAM1_segment_size__ = 0x00040000;

  __HEAPSIZE__ = 1024;
  __STACKSIZE__ = 4096;

  __vectors_load_start__ = __RAM1_segment_start__;
  .vectors __RAM1_segment_start__ : AT(__RAM1_segment_start__)
  {
    __vectors_start__ = .;
    *(.vectors .vectors.*)
  }
  __vectors_end__ = __vectors_start__ + SIZEOF(.vectors);
  __vectors_size__ = SIZEOF(.vectors);
  __vectors_load_end__ = __vectors_end__;

  . = ASSERT(__vectors_start__ == __vectors_end__ || (__vectors_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .vectors is too large to fit in RAM1 memory segment");

  __init_load_start__ = ALIGN(__vectors_end__ , 4);
  .init ALIGN(__vectors_end__ , 4) : AT(ALIGN(__vectors_end__ , 4))
  {
    __init_start__ = .;
    *(.init .init.*)
  }
  __init_end__ = __init_start__ + SIZEOF(.init);
  __init_size__ = SIZEOF(.init);
  __init_load_end__ = __init_end__;

  . = ASSERT(__init_start__ == __init_end__ || (__init_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .init is too large to fit in RAM1 memory segment");

  __text_load_start__ = ALIGN(__init_end__ , 4);
  .text ALIGN(__init_end__ , 4) : AT(ALIGN(__init_end__ , 4))
  {
    __text_start__ = .;
    *(.text .text.*)
  }
  __text_end__ = __text_start__ + SIZEOF(.text);
  __text_size__ = SIZEOF(.text);
  __text_load_end__ = __text_end__;

  . = ASSERT(__text_start__ == __text_end__ || (__text_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .text is too large to fit in RAM1 memory segment");

  __dtors_load_start__ = ALIGN(__text_end__ , 4);
  .dtors ALIGN(__text_end__ , 4) : AT(ALIGN(__text_end__ , 4))
  {
    __dtors_start__ = .;
    KEEP (*(SORT(.dtors.*))) KEEP (*(.dtors)) KEEP (*(.fini_array)) KEEP (*(SORT(.fini_array.*)))
  }
  __dtors_end__ = __dtors_start__ + SIZEOF(.dtors);
  __dtors_size__ = SIZEOF(.dtors);
  __dtors_load_end__ = __dtors_end__;

  . = ASSERT(__dtors_start__ == __dtors_end__ || (__dtors_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .dtors is too large to fit in RAM1 memory segment");

  __ctors_load_start__ = ALIGN(__dtors_end__ , 4);
  .ctors ALIGN(__dtors_end__ , 4) : AT(ALIGN(__dtors_end__ , 4))
  {
    __ctors_start__ = .;
    KEEP (*(SORT(.ctors.*))) KEEP (*(.ctors)) KEEP (*(.init_array)) KEEP (*(SORT(.init_array.*)))
  }
  __ctors_end__ = __ctors_start__ + SIZEOF(.ctors);
  __ctors_size__ = SIZEOF(.ctors);
  __ctors_load_end__ = __ctors_end__;

  . = ASSERT(__ctors_start__ == __ctors_end__ || (__ctors_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .ctors is too large to fit in RAM1 memory segment");

  __rodata_load_start__ = ALIGN(__ctors_end__ , 4);
  .rodata ALIGN(__ctors_end__ , 4) : AT(ALIGN(__ctors_end__ , 4))
  {
    __rodata_start__ = .;
    *(.rodata .rodata.*)
  }
  __rodata_end__ = __rodata_start__ + SIZEOF(.rodata);
  __rodata_size__ = SIZEOF(.rodata);
  __rodata_load_end__ = __rodata_end__;

  . = ASSERT(__rodata_start__ == __rodata_end__ || (__rodata_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .rodata is too large to fit in RAM1 memory segment");

  __srodata_load_start__ = ALIGN(__rodata_end__ , 4);
  .srodata ALIGN(__rodata_end__ , 4) : AT(ALIGN(__rodata_end__ , 4))
  {
    __srodata_start__ = .;
    *(.srodata .srodata.*)
  }
  __srodata_end__ = __srodata_start__ + SIZEOF(.srodata);
  __srodata_size__ = SIZEOF(.srodata);
  __srodata_load_end__ = __srodata_end__;

  . = ASSERT(__srodata_start__ == __srodata_end__ || (__srodata_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .srodata is too large to fit in RAM1 memory segment");

  __data_load_start__ = ALIGN(__srodata_end__ , 4);
  .data ALIGN(__srodata_end__ , 4) : AT(ALIGN(__srodata_end__ , 4))
  {
    __data_start__ = .;
    *(.data .data.*)
  }
  __data_end__ = __data_start__ + SIZEOF(.data);
  __data_size__ = SIZEOF(.data);
  __data_load_end__ = __data_end__;

  . = ASSERT(__data_start__ == __data_end__ || (__data_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .data is too large to fit in RAM1 memory segment");

  __tdata_load_start__ = ALIGN(__data_end__ , 4);
  .tdata ALIGN(__data_end__ , 4) : AT(ALIGN(__data_end__ , 4))
  {
    __tdata_start__ = .;
    *(.tdata .tdata.*)
  }
  __tdata_end__ = __tdata_start__ + SIZEOF(.tdata);
  __tdata_size__ = SIZEOF(.tdata);
  __tdata_load_end__ = __tdata_end__;

  . = ASSERT(__tdata_start__ == __tdata_end__ || (__tdata_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .tdata is too large to fit in RAM1 memory segment");

  __sdata_load_start__ = ALIGN(__tdata_end__ , 4);
  .sdata ALIGN(__tdata_end__ , 4) : AT(ALIGN(__tdata_end__ , 4))
  {
    __sdata_start__ = .;
    *(.sdata.* .sdata2.*)
  }
  __sdata_end__ = __sdata_start__ + SIZEOF(.sdata);
  __sdata_size__ = SIZEOF(.sdata);
  __sdata_load_end__ = __sdata_end__;

  . = ASSERT(__sdata_start__ == __sdata_end__ || (__sdata_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .sdata is too large to fit in RAM1 memory segment");

  __bss_load_start__ = ALIGN(__sdata_end__ , 4);
  .bss ALIGN(__sdata_end__ , 4) (NOLOAD) : AT(ALIGN(__sdata_end__ , 4))
  {
    __bss_start__ = .;
    *(.bss .bss.*) *(COMMON)
  }
  __bss_end__ = __bss_start__ + SIZEOF(.bss);
  __bss_size__ = SIZEOF(.bss);
  __bss_load_end__ = __bss_end__;

  . = ASSERT(__bss_start__ == __bss_end__ || (__bss_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .bss is too large to fit in RAM1 memory segment");

  __tbss_load_start__ = ALIGN(__bss_end__ , 4);
  .tbss ALIGN(__bss_end__ , 4) (NOLOAD) : AT(ALIGN(__bss_end__ , 4))
  {
    __tbss_start__ = .;
    *(.tbss .tbss.*)
  }
  __tbss_end__ = __tbss_start__ + SIZEOF(.tbss);
  __tbss_size__ = SIZEOF(.tbss);
  __tbss_load_end__ = __tbss_end__;

  . = ASSERT(__tbss_start__ == __tbss_end__ || (__tbss_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .tbss is too large to fit in RAM1 memory segment");

  __sbss_load_start__ = ALIGN(__tbss_end__ , 4);
  .sbss ALIGN(__tbss_end__ , 4) (NOLOAD) : AT(ALIGN(__tbss_end__ , 4))
  {
    __sbss_start__ = .;
    *(.sbss .sbss.*)
  }
  __sbss_end__ = __sbss_start__ + SIZEOF(.sbss);
  __sbss_size__ = SIZEOF(.sbss);
  __sbss_load_end__ = __sbss_end__;

  . = ASSERT(__sbss_start__ == __sbss_end__ || (__sbss_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .sbss is too large to fit in RAM1 memory segment");

  __non_init_load_start__ = ALIGN(__sbss_end__ , 4);
  .non_init ALIGN(__sbss_end__ , 4) (NOLOAD) : AT(ALIGN(__sbss_end__ , 4))
  {
    __non_init_start__ = .;
    *(.non_init .non_init.*)
  }
  __non_init_end__ = __non_init_start__ + SIZEOF(.non_init);
  __non_init_size__ = SIZEOF(.non_init);
  __non_init_load_end__ = __non_init_end__;

  . = ASSERT(__non_init_start__ == __non_init_end__ || (__non_init_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .non_init is too large to fit in RAM1 memory segment");


  __heap_load_start__ = ALIGN(__non_init_end__ , 4);
  .heap ALIGN(__non_init_end__ , 4) (NOLOAD) : AT(ALIGN(__non_init_end__ , 4))
  {
    __heap_start__ = .;
    *(.heap .heap.*)
    . = ALIGN(MAX(__heap_start__ + __HEAPSIZE__ , .), 4);
  }
  __heap_end__ = __heap_start__ + SIZEOF(.heap);
  __heap_size__ = SIZEOF(.heap);
  __heap_load_end__ = __heap_end__;

  . = ASSERT(__heap_start__ == __heap_end__ || (__heap_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .heap is too large to fit in RAM1 memory segment");


  __stack_load_start__ = __RAM1_segment_start__ + (__RAM1_segment_size__ - __STACKSIZE__);
  .stack __RAM1_segment_start__ + (__RAM1_segment_size__ - __STACKSIZE__) (NOLOAD) : AT(__RAM1_segment_start__ + (__RAM1_segment_size__ - __STACKSIZE__))
  {
    __stack_start__ = .;
    *(.stack .stack.*)
    . = ALIGN(MAX(__stack_start__ + __STACKSIZE__ , .), 4);
  }
  __stack_end__ = __stack_start__ + SIZEOF(.stack);
  __stack_size__ = SIZEOF(.stack);
  __stack_load_end__ = __stack_end__;

  __RAM1_segment_used_end__ = __RAM1_segment_start__ + (__RAM1_segment_size__ - __STACKSIZE__) + SIZEOF(.stack);
  __RAM1_segment_used_size__ = __RAM1_segment_used_end__ - __RAM1_segment_start__;

  . = ASSERT(__stack_start__ == __stack_end__ || (__stack_end__ - __RAM1_segment_start__) <= __RAM1_segment_size__ , "error: .stack is too large to fit in RAM1 memory segment");
  . = ASSERT(__heap_end__ <= __stack_start__ , "error: section .heap overlaps absolute placed section .stack");

}

