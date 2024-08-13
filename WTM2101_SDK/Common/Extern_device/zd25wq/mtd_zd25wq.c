/**
* @file    MTD-ZD25WQ.c
* @brief   The Source Codes for the ZD25WQ Functions
* @version V1.0.0.0
* @date    2023/04/13
* DO NOT USE THIS SOFTWARE WITHOUT THE SOFTWARE LISENCE AGREEMENT.
*
* (C)Copyright WITIN Technology Co.Ltd 2023 All rights reserved
*/
#include "mtd_zd25wq.h"

int zd25wq_mtd_init(struct __Mtd_Info * mtd)
{
    int ret = 0;
    ZD25WQ *ZD25WQ_hd = (ZD25WQ *)(mtd->userdata);
  
    if(mtd == NULL) return  -1;
    
    ret = ZD25WQ_qspi_init(ZD25WQ_hd);
    if(ret <= 0) return  -2;
    
    ret = ZD25WQ_open(ZD25WQ_hd,QSPI,ZD25WQ_QSPI_1LINE,DISABLE,0,DISABLE,0);
     if(ret <= 0) return  -3;

    if (ZD25WQ_hd->flash_size < (mtd->blockstart + mtd->blockcount)*mtd->pageszie*mtd->blocksize)
    {
        ZD25WQ_close(ZD25WQ_hd);
        return  -4;
    }

    return 1;
}

int zd25wq_mtd_exit(struct __Mtd_Info * mtd)
{
    int ret = 0;
    if(mtd == NULL) return  -1;

    ret = ZD25WQ_close((ZD25WQ *)(mtd->userdata));
    if(ret <= 0) return  -2;

    return 1;
}

int zd25wq_mtd_protect(struct __Mtd_Info *mtd, uint8_t flag)
{
    int ret = 0;
    if(mtd == NULL) return  -1;

    ret = ZD25WQ_chip_write_protect((ZD25WQ *)(mtd->userdata),flag);
    if(ret <= 0) return  -2;

    return 1;
}

int zd25wq_mtd_erase(struct __Mtd_Info *mtd, uint32_t block_id)
{
    if(mtd == NULL) return  -1;
    ZD25WQ *ZD25WQ_hd = (ZD25WQ *)(mtd->userdata);

    ZD25WQ_sector_or_block_erase(ZD25WQ_hd, ZD25WQ_SECTOR_ERASE,block_id*mtd->blocksize*mtd->pageszie);
    
    return 1;
}

int zd25wq_mtd_pread(struct __Mtd_Info *mtd, uint32_t block_id, uint32_t chunk_id, uint8_t *data)
{
    int read_size = 0;
    uint address = 0;
    if(mtd == NULL) return  -1;
    ZD25WQ *ZD25WQ_hd = (ZD25WQ *)(mtd->userdata);

    address = (block_id*mtd->blocksize + chunk_id)*mtd->pageszie;
    read_size = ZD25WQ_read(ZD25WQ_hd, address, data,mtd->pageszie);

    return 1;
}

int zd25wq_mtd_pwrite(struct __Mtd_Info *mtd, uint32_t block_id, uint32_t chunk_id, uint8_t *data)
{
    int index = 0, total = 0;
    uint address =0;
    if(mtd == NULL) return  -1;
    if(data == NULL) return  -2;
    ZD25WQ *ZD25WQ_hd = (ZD25WQ *)(mtd->userdata);

    total = mtd->pageszie / ZD25WQ_hd->page_size;
    address = ((block_id)*mtd->blocksize + chunk_id)*mtd->pageszie;
    while (index < total)
    {
        ZD25WQ_write(ZD25WQ_hd, address, data,ZD25WQ_hd->page_size);
        address += ZD25WQ_hd->page_size;
        data += ZD25WQ_hd->page_size;
        index++;
    }

    return 1;
}
