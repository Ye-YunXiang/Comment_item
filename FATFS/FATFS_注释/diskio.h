/*-----------------------------------------------------------------------/
/  Low level disk interface modlue include file   (C)ChaN, 2014          /
/-----------------------------------------------------------------------*/
// 低级硬盘接口模块

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#define _USE_WRITE	1	/* 1: Enable disk_write function 开启disk_write 函数*/
#define _USE_IOCTL	1	/* 1: Enable disk_ioctl fucntion 开启 disk_ioctl 函数*/

#include "integer.h"		// C++定义重载类


/* Status of Disk Functions 	硬盘功能状态*/
typedef BYTE	DSTATUS;

/* Results of Disk Functions  磁盘函数结果 */
typedef enum {
	RES_OK = 0,		/* 0: Successful  成功*/
	RES_ERROR,		/* 1: R/W Error  错误*/
	RES_WRPRT,		/* 2: Write Protected 写入保护 */
	RES_NOTRDY,		/* 3: Not Ready  没有准备好*/
	RES_PARERR		/* 4: Invalid Parameter  无效的参数*/
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */
// 磁盘控制函数原型，都是返回byte类型。


DSTATUS disk_initialize (BYTE pdrv);		// 磁盘初始化
DSTATUS disk_status (BYTE pdrv);			// 磁盘状态
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);	
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


/* Disk Status Bits (DSTATUS) 磁盘状态位*/

#define STA_NOINIT		0x01	/* Drive not initialized  驱动未初始化*/
#define STA_NODISK		0x02	/* No medium in the drive 驱动器中没有介质*/
#define STA_PROTECT		0x04	/* Write protected 写入保护*/


/* Command code for disk_ioctrl fucntion  disk_ioctrl的函数命令代码*/

/* Generic command (Used by FatFs) 通用命令*/
#define CTRL_SYNC			0	/* Complete pending write process 完成挂起的写进程(needed at _FS_READONLY == 0) */
#define GET_SECTOR_COUNT	1	/* Get media size 获取媒体大小 (needed at _USE_MKFS == 1) */
#define GET_SECTOR_SIZE		2	/* Get sector size 获取扇区大小(needed at _MAX_SS != _MIN_SS) */
#define GET_BLOCK_SIZE		3	/* Get erase block size 获取擦除快的大小 (needed at _USE_MKFS == 1) */
#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used 通知设备扇区块上的数据不在被使用 (needed at _USE_TRIM == 1) */

/* Generic command (Not used by FatFs) */
#define CTRL_POWER			5	/* Get/Set power status 获取/设置 电源状态*/
#define CTRL_LOCK			6	/* Lock/Unlock media removal  锁定/解锁 介质移除*/
#define CTRL_EJECT			7	/* Eject media 弹出介质*/
#define CTRL_FORMAT			8	/* Create physical format on the media 在介质上创建物理格式*/

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision 获取F/W修改*/
#define ATA_GET_MODEL		21	/* Get model name  获取模型的名称*/
#define ATA_GET_SN			22	/* Get serial number 获取序列号*/

#ifdef __cplusplus
}
#endif

#endif
