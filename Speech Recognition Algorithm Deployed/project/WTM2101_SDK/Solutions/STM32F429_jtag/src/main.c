#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include "jtag_port.h"
#include "bin_file.h"


void main(void) 
{
   DEBUG_PRINT("jtag test\n\r");

   Jtag_Io_Config();
   Jtag_Download_Bin(__bin_file, sizeof(__bin_file));
   while(1);

}

/*************************** End of file ****************************/