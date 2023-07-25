/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs  用于fat的低级磁盘i/o模块骨架   (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
/*如果有可用的工作存储控制模块，则应通过胶水功能将其粘贴到fatf上，而不是修改gatf。
这是一个使用已定义API将各现有存储控制模块连接到fatf模块的粘和函数示例。*/


#include "diskio.h"		/* FatFs lower layer API  下层API*/
#include "./flash/bsp_spi_flash.h"
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module 例如：现有USB MSD控制模块的头文件。*/
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module 例如：现有ATA勇攀控制模块的头文件。*/
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module 示例：已存在的MMC/SDC控制模块头文件。*/

/* Definitions of physical drive number for each drive 每个驱动器的物理驱动器号的定义*/
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0  示例：将ATA硬盘映射到物理磁盘0*/
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 示例：映射MMC/SD卡到物理磁盘1*/
#define USB		2	/* Example: Map USB MSD to physical drive 2  示例：映射USB MSD到物理磁盘2*/	


#define SD_CARD   0
#define SPI_FLASH 1


/*-----------------------------------------------------------------------*/
/* Get Drive Status  	获取驱动器状态                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive *标识驱动器的物理驱动器号*/
)
{
	DSTATUS stat;
//	int result;

	switch (pdrv) {
		case SD_CARD :
	//		result = ATA_disk_status();

			// translate the reslut code here	在这里翻译结果代码

			return stat;

		case SPI_FLASH :		

			// 这里一块和下面的是遗留物，要自己改写
			// 改写就和下面差不多，通过SPI或者啥去读取FLASH的ID，看看我们配置的和FLASH对不对的上。
			// 对不上的话后面就没办法正常读写什么的，或者读写的盘不是我们设置的盘。

			if (SPI_FLASH_ReadID() == sFLASH_ID)	//这里记得要改写，意思就是SPI去读设备返回的ID，去和我们预定的ID对比一下设备对不对。
			{
				//状态正常
				stat = 0;
			}
			else
			{
				//状态不正常
				stat = STA_NOINIT;		
			}

			return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                初始化驱动器                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive 标识驱动器的物理驱动器号*/
)
{
	DSTATUS stat;
//	int result;

	// 经典开始选择存储
	switch (pdrv) {			
		case SD_CARD :		
	//		result = ATA_disk_initialize();

			// translate the reslut code here

			return stat;

		case SPI_FLASH :
			

			// 咣咣把初始化代码往这怼就完了
			SPI_FLASH_Init();
			SPI_Flash_WAKEUP();
	//		result = MMC_disk_initialize();
		

			return  disk_status(SPI_FLASH);

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)       阅读扇区                                                 */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive  物理驱动器号，用于标识驱动器*/
	BYTE *buff,		/* Data buffer to store read data  存储读数据的数据缓冲区*/
	DWORD sector,	/* Sector address in LBA LBA扇区地址*/
	UINT count		/* Number of sectors to read  要读取的扇区*/
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case SD_CARD :
		// translate the arguments here	转换之类的参数

//		result = ATA_disk_read(buff, sector, count);

		// translate the reslut code here	转换这里的代码

		return res;

	case SPI_FLASH :


		/* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
		// 下面两行都是之前野火例程里面阿达，可以删除
		sector += 512;
		SPI_FLASH_BufferRead(buff,sector*4096,count*4096);

		res = RES_OK;

	
		return res;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)       写入扇区                                               */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive  用于标识驱动器的物理驱动器号*/
	const BYTE *buff,	/* Data to be written    写入数据*/
	DWORD sector,		/* Sector address in LBA   LBA扇区地址*/
	UINT count			/* Number of sectors to write   要写入的扇区*/
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case SD_CARD :
		// translate the arguments here  转换这里的参数

//		result = ATA_disk_write(buff, sector, count);

		// translate the reslut code here	转换这里的代码

		return res;

	case SPI_FLASH :

		//## 下面这一坨也是野火的，可以借鉴删除。
		/* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
		sector += 512;
		//一定要先擦除再写入
		SPI_FLASH_SectorErase(sector*4096);
		SPI_FLASH_BufferWrite((u8 *)buff,sector*4096,count*4096);

		res = RES_OK;
	
		return res;


	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions     其他功能                                          */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..)  物理驱动器号*/
	BYTE cmd,		/* Control code 控制码*/
	void *buff		/* Buffer to send/receive control data 发送/接收控制数据的缓冲区*/
)
{
	DRESULT res;

	switch (pdrv) {
	case SD_CARD :

		// Process of the command for the ATA drive  ATA磁盘命令进程

		return res;

	case SPI_FLASH :
		

		// #喔嚯，套了个switch，不同参数实现不同功能吧。
		switch(cmd)
		{
			//返回扇区个数
			case GET_SECTOR_COUNT:
				/* 扇区数量：1536*4096/1024/1024=6(MB) */
				*(DWORD*)buff = 1536;
				
			break;
			//返回每个扇区大小
			case GET_SECTOR_SIZE:
				*(WORD*)buff = 4096;

			break;
			//返回擦除扇区的最小个数（单位为扇区）
			case GET_BLOCK_SIZE:
			 *(WORD*)buff = 1;
			
			break;
			
		}		
			

		// Process of the command for the MMC/SD card  MMC/SD 命令进程
		res = RES_OK;
		return res;

	}

	return RES_PARERR;
}
#endif

//返回时间
DWORD get_fattime (void)
{

	return 0;
}
