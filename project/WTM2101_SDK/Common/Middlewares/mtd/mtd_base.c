#include "mtd_base.h"
#include "string.h"
#include "heap.h"

int mtd_init(Mtd_Info *mtd)
{
    /************************************************************************

                    一个MTD文件需要提供一个Mtd_Info信息，以便于注册

    ************************************************************************/
    int re = 0;
    if (mtd == NULL)
        return -1;

    mtd->mtd_init_flag = MTD_INIT_ERROR;
    re = mtd->init(mtd);
    if (re > 0) mtd->mtd_init_flag = MTD_INIT_OK;
    if (mtd->type == MTD_TYPE_NORFLASH)
    {
        mtd->oobsize = 0x00;
    }
    return re < 0 ? -3 + re : re;
}

int mtd_exit(Mtd_Info *mtd)
{
    mtd->mtd_init_flag = MTD_INIT_ERROR;
    int re = mtd->exit(mtd);

    return re < 0 ? -1 + re : re;
}

int mtd_protect(Mtd_Info *mtd,uchar flag)
{
    int re = 0;
    if (mtd == NULL)
        return -1;

    re = mtd->protect(mtd,flag);
    if(re <= 0) return -2;

    return 1;
}

int mtd_write(Mtd_Info *mtd, int sub_fd, uchar *buf, uint len)
{
    uint wlen = len;
    int block_id = 0, page_id = 0,offset = 0,slen = 0;
    uchar *  cache = NULL,*temp = NULL;

    if (mtd->type != MTD_TYPE_NORFLASH && (mtd->oobsize + len >= mtd->blocksize*mtd->blockcount*mtd->pageszie))
        return -1;
    if (mtd->mtd_init_flag == MTD_INIT_ERROR) return -2;

    //计算当前偏移对应的块和页,页内偏移
    block_id = (mtd->oobsize / mtd->pageszie) / mtd->blocksize + mtd->blockstart;
    page_id = (mtd->oobsize / mtd->pageszie)% mtd->blocksize ;
    offset = mtd->oobsize%mtd->pageszie;
    cache = pvPortMalloc(mtd->pageszie);
    if (cache == NULL)
            return -3;
    if (offset != 0x00)
    {
        if (mtd->pread(mtd, block_id, page_id, cache) < 0)
        {
            vPortFree(cache);
            return -4;
        }
        if (offset + len <= mtd->pageszie)
            slen = len;
        else
            slen = len > mtd->pageszie ? mtd->pageszie : mtd->pageszie - offset;
        if (memcmp(cache + offset, buf, slen) != 0)
        {
            //数据不一致
            memcpy(cache + offset, buf, slen);
            if (page_id == 0x00 && mtd->blocksize == 0x01 && mtd->pageszie == mtd->erasesize)
            {//需要进行擦除操作，不然写入的数据无效
                    if (mtd->erase(mtd, block_id) <= 0)
                    {
                            vPortFree(cache);
                            return -5;
                    }
            }
            if (mtd->pwrite(mtd, block_id, page_id, cache) <= 0)
            {
                    vPortFree(cache);
                    return -6;
            }
        }
        len -= slen;
        offset = 0x00;
        page_id += 1;
        buf += slen;
        if (page_id >= mtd->blocksize)
        {
            page_id = 0x00;
            block_id += 1;
        }
    }
    while (len > 0x00)
    {
        if (len < mtd->pageszie)
        {
            if (mtd->pread(mtd, block_id, page_id, cache) <= 0)
            {
                vPortFree(cache);
                return -7;
            }
            if (memcmp(cache, buf, len) == 0)
            {
                //不用回写了，因为是一样的内容
                break;
            }
            memcpy(cache, buf, len);
            temp = cache;
            len = 0;
        }
        else
        {
            temp = buf;
            len -= mtd->pageszie;
        }
        if (page_id == 0x00 && mtd->blocksize == 0x01 && mtd->pageszie == mtd->erasesize)
        {
            //需要进行擦除操作，不然写入的数据无效
            if (mtd->erase(mtd, block_id) < 0)
            {
                vPortFree(cache);
                return -8;
            }
        }
        if (mtd->pwrite(mtd, block_id, page_id, temp) <= 0)
        {
            vPortFree(cache);
            return -9;
        }
        page_id += 1;
        buf += mtd->pageszie;
        if (page_id >= mtd->blocksize)
        {
            page_id = 0x00;
            block_id += 1;
        }
    }
    mtd->oobsize += wlen;
    vPortFree(cache);

    return 1;
}

int mtd_read(Mtd_Info *mtd, int sub_fd, uchar *buf, uint len)
{
    uint wlen = len;
    int block_id = 0, page_id = 0, offset = 0, slen = 0;
    uchar *  cache = NULL;

    if (mtd->type != MTD_TYPE_NORFLASH && (mtd->oobsize + len >= mtd->blocksize*mtd->blockcount*mtd->pageszie))
            return -1;
    if (mtd->mtd_init_flag == MTD_INIT_ERROR) return -2;

    //计算当前偏移对应的块和页,页内偏移
    block_id = (mtd->oobsize / mtd->pageszie) / mtd->blocksize + mtd->blockstart;
    page_id = (mtd->oobsize / mtd->pageszie) % mtd->blocksize;
    offset = mtd->oobsize%mtd->pageszie;
    cache = pvPortMalloc(mtd->pageszie);
    if (cache == NULL)
        return -3;
    if (offset != 0x00)
    {
        if (mtd->pread(mtd, block_id, page_id, cache) <= 0)
        {
            vPortFree(cache);
            return -4;
        }
        if (offset + len <= mtd->pageszie)
            slen = len;
        else
            slen = len > mtd->pageszie ? mtd->pageszie : mtd->pageszie - offset;

        memcpy(buf, cache + offset, slen);
        len -= slen;
        offset = 0x00;
        page_id += 1;
        buf += slen;
        if (page_id >= mtd->blocksize)
        {
            page_id = 0x00;
            block_id += 1;
        }
    }
    while (len > 0x00)
    {
        if (len < mtd->pageszie)
        {
            if (mtd->pread(mtd, block_id, page_id, cache) <= 0)
            {
                vPortFree(cache);
                return -5;
            }
            memcpy(buf, cache, len);
            len = 0;
        }
        else
        {
            if (mtd->pread(mtd, block_id, page_id, buf) <= 0)
            {
                vPortFree(cache);
                return -6;
            }
            len -= mtd->pageszie;
        }
        page_id += 1;
        buf += mtd->pageszie;
        if (page_id >= mtd->blocksize)
        {
            page_id = 0x00;
            block_id += 1;
        }
    }

    offset += mtd->nor_base + mtd->oobsize;
    mtd->oobsize += wlen;
    vPortFree(cache);

    return 1;
}

int mtd_lseek(Mtd_Info *mtd, int sub_fd, int  offset, int  pos)
{
    if (mtd->mtd_init_flag == MTD_INIT_ERROR)
        return -1;
    if (mtd->type != MTD_TYPE_NORFLASH)
        return -2;
    if (pos > MTD_END || pos < MTD_SET)
        return -3;

    if (pos == MTD_CUR)
        offset += mtd->oobsize;
    else if (pos == MTD_END)
        offset += mtd->blockcount*mtd->blocksize*mtd->pageszie-1;

    if (offset < 0x00 || offset >= mtd->blockcount*mtd->blocksize*mtd->pageszie)
        return -4;

    mtd->oobsize = offset;

    return offset;
}
