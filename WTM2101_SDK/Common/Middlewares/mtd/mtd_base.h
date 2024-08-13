#ifndef __MTD_BASE__
#define __MTD_BASE__

#ifndef MTD_SAFE_CHECK
#define MTD_SAFE_CHECK    1
#endif

#define MTD_DEV_NOR_SUPPORT_XIP (0x01<<0)
#define MTD_SET	0
#define MTD_CUR 1
#define MTD_END	2

#define MTD_INIT_ERROR	0
#define MTD_INIT_OK		(!MTD_INIT_ERROR)

typedef unsigned int uint;
typedef unsigned char uchar;

typedef enum
{
 MTD_TYPE_ABSENT		 =  0,
 MTD_TYPE_RAM			 ,
 MTD_TYPE_ROM			 ,
 MTD_TYPE_NORFLASH		 ,
 MTD_TYPE_NANDFLASH		 ,
 MTD_TYPE_DATAFLASH		 ,
 MTD_TYPE_UBIVOLUME		 ,

}Mtd_Type;

#define MTD_FLAGS_WRITEABLE         0X01
#define MTD_FLAGS_BIT_WRITEABLE     0X02
#define MTD_FLAGS_NO_ERASE          0X04
#define MTD_FLAGS_XIP               0X08

typedef struct __Erase_Info {
    uint  block_id; //擦除块号
    uint  zone_id;//区域号
    uchar all;//全部擦除
}Erase_Info;

typedef enum
{
    MIT_FSMC = 0,
    MIT_SPI_CORE,
    MIT_I2C_CORE,
    MIT_NONE = 128,
}Mtd_Interface_Type;

typedef enum
{
    MET_SOFT = 0,
    MET_HARDWARE,
}Mtd_Ecc_Type;

#pragma pack(push)
#pragma pack(1)
typedef struct __Mtd_Info
{
    uchar	 mtd_init_flag; //设备初始化标志
    Mtd_Type type;              //设备类型
    const char * name;          //设备名字
    uint     flags;             //设备特性标志
    Mtd_Interface_Type mit;     //设备访问接口类型
    Mtd_Ecc_Type  met;          //mtd设备的   ECC特性
    const char * mit_path;      //如果是   SPI或者  I2C 设备 ,  当注册到内核后,可以通过总线发起访问,此接口预留未来使用
    uint     blockstart;        //开始块序号,因为多分区问题，所以需要提供不为0 的起点。
    uint     blocksize;         //设备的块大小,代表每个块有多少页
    uint     blockcount;        //块数量  ,   通过计算      blocksize * blockcount *  pageszie * zoneofblocks可以得到    MTD设备 管理的内存大小
    uint     pageszie;          //页大小，代表每一页有多少字节
    int      erasesize;         //擦除大小，一般是块大小，但有时设备有多个擦除单位
    int      writesize;         //写单位大小
    int      oobsize;           //
    uint     nor_base;          //nor基地址
    int      zoneofblocks;      //1个区域多少block，
    void *   userdata;          //自定义数据

    int(*init)(struct __Mtd_Info * mtd);
    int(*exit)(struct __Mtd_Info * mtd);
    int(*protect) (struct __Mtd_Info *mtd, uchar flag);
    int(*erase) (struct __Mtd_Info *mtd, uint eindex);
    int(*pread)  (struct __Mtd_Info *mtd, uint block_id , uint chunk_id , uchar *data);
    int(*pwrite) (struct __Mtd_Info *mtd, uint block_id , uint chunk_id,  uchar *data);
    int(*pread_full)  (struct __Mtd_Info *mtd, uint block_id, uint chunk_id, uchar *data,uchar *oob_data, uint oob_len);
    int(*pwrite_full) (struct __Mtd_Info *mtd, uint block_id, uint chunk_id, uchar *data,uchar *oob_data, uint oob_len);
    union
    {
        struct
        {
            int(*lread)(struct __Mtd_Info *mtd, uint block_id, uint chunk_id, uchar *data, uint offset, uint len);
            int(*lwrite)(struct __Mtd_Info *mtd, uint block_id, uint chunk_id, uchar *data, uint offset, uint len);
            int searse;// self - earse，自擦除功能...如此功能关闭，则，底层必须实现擦除能力
            void *nor_small_data;
        }nor;
        struct
        {
            int(*read_oob) (struct __Mtd_Info *mtd, uint block_id, uint page_id, uchar *data, uint oob_len);
            int(*write_oob) (struct __Mtd_Info *mtd, uint block_id, uint page_id, uchar *data, uint oob_len);
            int(*block_isbad) (struct __Mtd_Info *mtd,uint block_id);
            int(*block_markbad) (struct __Mtd_Info *mtd, uint block_id);
        }nand;

    }exfun;

    struct __Mtd_Info *next;//块设备链，用于解决磁盘多分区问题
}Mtd_Info;
#pragma pack(pop)

/**
* @brief  Init the mtd device structure
* @param  mtd: the __Mtd_Info structure instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int mtd_init(Mtd_Info *mtd);

/**
* @brief  Uninit the mtd device structure
* @param  mtd: the __Mtd_Info structure instance
* @retval Greater than 0 for success, otherwise failure
*/
extern int mtd_exit(Mtd_Info *mtd);

/**
* @brief  Write data to the mtd device
* @param  mtd: the __Mtd_Info structure instance
* @param  sub_fd: if there are many devices,the sub_fd represent the device index, the current only support the one device.so the sub_fd must be 0
* @param  buf: the write data buffer
* @param  len: the write data buffer size
* @retval Greater than or equal to 0 for write data size, otherwise failure
*/
extern int mtd_write(Mtd_Info *mtd, int sub_fd, uchar *buf, uint len);

/**
* @brief  Read data from the mtd device
* @param  mtd: the __Mtd_Info structure instance
* @param  sub_fd: if there are many devices,the sub_fd represent the device index, the current only support the one device.so the sub_fd must be 0
* @param  buf: the read data buffer
* @param  len: the read data buffer size
* @retval Greater than or equal to 0 for read data size, otherwise failure
*/
extern int mtd_read(Mtd_Info *mtd, int sub_fd, uchar *buf, uint len);

/**
* @brief  Seek the data index in the mtd device
* @param  mtd: the __Mtd_Info structure instance
* @param  sub_fd: if there are many devices,the sub_fd represent the device index, the current only support the one device.so the sub_fd must be 0
* @param  offset: the offset size
* @param  pos: the start position,only can be MTD_SET or MTD_CUR or MTD_END
* @retval Greater than or equal to 0 for seek position, otherwise failure
*/
extern int mtd_lseek(Mtd_Info *mtd, int sub_fd, int  offset, int  pos);


#endif
