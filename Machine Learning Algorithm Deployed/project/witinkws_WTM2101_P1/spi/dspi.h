#ifndef _DSPI_H
#define _DSPI_H

#include "wtm2101.h"
#include "gpio.h"
#include "spi.h"
#include "dma.h"

#include "vfs_list.h"
#include "spi_transfer_protocol.h"

#include "string.h"
#include <stdarg.h>

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    SPI_TypeDef *spi_hd;
    vfs_list_type *slist, *rlist, *alist;
    Lframe_ctol frame_ctl;
}Dspi;
#pragma pack(pop)

/**
* @brief  init spi slave device and transport protocol 
* @param  None
* @retval the dspi driver pointer if success,other failure 
*/
extern Dspi *dspi_open(void);

/**
* @brief  write buf-data to dspi driver send-list  
* @param  buf:the write data
* @len    len:the write data length
* @retval greater than 0 if success,other failure 
*/
extern int dspi_write(Dspi *dspi_hd,uint8_t *buf,int len);

/**
* @brief  from dspi driver receive-list to read data   
* @param  buf:the read data
* @len    len:the read data length
* @retval greater than 0 if success,other failure 
*/
extern int dspi_read(Dspi *dspi_hd,uint8_t *buf,int *len);

///**
//* @brief  from dspi driver receive-list to read data   
//* @param  buf:the read data
//* @len    len:the read data length
//* @retval greater than 0 if success,other failure 
//*/
extern int dspi_ctl(Dspi *dspi_hd,int command, ...);

#endif
