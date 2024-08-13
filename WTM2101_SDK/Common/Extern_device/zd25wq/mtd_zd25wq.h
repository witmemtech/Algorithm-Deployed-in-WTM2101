/** Define to Prevent Recursive Inclusion */
#ifndef MTDZD25WQ_H
#define MTDZD25WQ_H

#ifdef __cplusplus
extern "C" {
#endif 

/** Includes */
#include "zd25wq.h"
#include "mtd_base.h"

/**
* @brief  Init the ZD25WQ flash and Adapta the mtd base
* @param  mtd: the __Mtd_Info structure instance 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int zd25wq_mtd_init(struct __Mtd_Info * mtd);

/**
* @brief  Uninit the ZD25WQ flash and Adapta the mtd base
* @param  mtd: the __Mtd_Info structure instance 
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int zd25wq_mtd_exit(struct __Mtd_Info * mtd);

/**
* @brief  Write protect the ZD25WQ flash and Adapta the mtd base
* @param  mtd: the __Mtd_Info structure instance 
* @param  flag: enable or diable write protect
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int zd25wq_mtd_protect(struct __Mtd_Info *mtd, uint8_t flag);

/**
* @brief  Erase the ZD25WQ flash and Adapta the mtd base
* @param  mtd: the __Mtd_Info structure instance 
* @param  block_id: the mtd device block id
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int zd25wq_mtd_erase(struct __Mtd_Info *mtd, uint32_t block_id);

/**
* @brief  Read the ZD25WQ flash and Adapta the mtd base
* @param  mtd: the __Mtd_Info structure instance 
* @param  block_id: the mtd device block id
* @param  chunk_id: the mtd device chunk id
* @param  data: the read data buffer
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int zd25wq_mtd_pread(struct __Mtd_Info *mtd, uint32_t block_id, uint32_t chunk_id, uint8_t *data);

/**
* @brief  Write the ZD25WQ flash and Adapta the mtd base
* @param  mtd: the __Mtd_Info structure instance 
* @param  block_id: the mtd device block id
* @param  chunk_id: the mtd device chunk id
* @param  data: the write data buffer
* @retval Greater than 0 for success, otherwise failure
*/ 
extern int zd25wq_mtd_pwrite(struct __Mtd_Info *mtd, uint32_t block_id, uint32_t chunk_id, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif    
