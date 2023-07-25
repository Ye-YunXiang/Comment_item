/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs  ����fat�ĵͼ�����i/oģ��Ǽ�   (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
/*����п��õĹ����洢����ģ�飬��Ӧͨ����ˮ���ܽ���ճ����fatf�ϣ��������޸�gatf��
����һ��ʹ���Ѷ���API�������д洢����ģ�����ӵ�fatfģ���ճ�ͺ���ʾ����*/


#include "diskio.h"		/* FatFs lower layer API  �²�API*/
#include "./flash/bsp_spi_flash.h"
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module ���磺����USB MSD����ģ���ͷ�ļ���*/
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module ���磺����ATA���ʿ���ģ���ͷ�ļ���*/
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module ʾ�����Ѵ��ڵ�MMC/SDC����ģ��ͷ�ļ���*/

/* Definitions of physical drive number for each drive ÿ���������������������ŵĶ���*/
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0  ʾ������ATAӲ��ӳ�䵽�������0*/
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 ʾ����ӳ��MMC/SD�����������1*/
#define USB		2	/* Example: Map USB MSD to physical drive 2  ʾ����ӳ��USB MSD���������2*/	


#define SD_CARD   0
#define SPI_FLASH 1


/*-----------------------------------------------------------------------*/
/* Get Drive Status  	��ȡ������״̬                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive *��ʶ��������������������*/
)
{
	DSTATUS stat;
//	int result;

	switch (pdrv) {
		case SD_CARD :
	//		result = ATA_disk_status();

			// translate the reslut code here	�����﷭��������

			return stat;

		case SPI_FLASH :		

			// ����һ���������������Ҫ�Լ���д
			// ��д�ͺ������࣬ͨ��SPI����ɶȥ��ȡFLASH��ID�������������õĺ�FLASH�Բ��Ե��ϡ�
			// �Բ��ϵĻ������û�취������дʲô�ģ����߶�д���̲����������õ��̡�

			if (SPI_FLASH_ReadID() == sFLASH_ID)	//����ǵ�Ҫ��д����˼����SPIȥ���豸���ص�ID��ȥ������Ԥ����ID�Ա�һ���豸�Բ��ԡ�
			{
				//״̬����
				stat = 0;
			}
			else
			{
				//״̬������
				stat = STA_NOINIT;		
			}

			return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                ��ʼ��������                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive ��ʶ��������������������*/
)
{
	DSTATUS stat;
//	int result;

	// ���俪ʼѡ��洢
	switch (pdrv) {			
		case SD_CARD :		
	//		result = ATA_disk_initialize();

			// translate the reslut code here

			return stat;

		case SPI_FLASH :
			

			// ���۰ѳ�ʼ����������������
			SPI_FLASH_Init();
			SPI_Flash_WAKEUP();
	//		result = MMC_disk_initialize();
		

			return  disk_status(SPI_FLASH);

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)       �Ķ�����                                                 */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive  �����������ţ����ڱ�ʶ������*/
	BYTE *buff,		/* Data buffer to store read data  �洢�����ݵ����ݻ�����*/
	DWORD sector,	/* Sector address in LBA LBA������ַ*/
	UINT count		/* Number of sectors to read  Ҫ��ȡ������*/
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case SD_CARD :
		// translate the arguments here	ת��֮��Ĳ���

//		result = ATA_disk_read(buff, sector, count);

		// translate the reslut code here	ת������Ĵ���

		return res;

	case SPI_FLASH :


		/* ����ƫ��2MB���ⲿFlash�ļ�ϵͳ�ռ����SPI Flash����6MB�ռ� */
		// �������ж���֮ǰҰ���������氢�����ɾ��
		sector += 512;
		SPI_FLASH_BufferRead(buff,sector*4096,count*4096);

		res = RES_OK;

	
		return res;

	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)       д������                                               */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive  ���ڱ�ʶ��������������������*/
	const BYTE *buff,	/* Data to be written    д������*/
	DWORD sector,		/* Sector address in LBA   LBA������ַ*/
	UINT count			/* Number of sectors to write   Ҫд�������*/
)
{
	DRESULT res;
//	int result;

	switch (pdrv) {
	case SD_CARD :
		// translate the arguments here  ת������Ĳ���

//		result = ATA_disk_write(buff, sector, count);

		// translate the reslut code here	ת������Ĵ���

		return res;

	case SPI_FLASH :

		//## ������һ��Ҳ��Ұ��ģ����Խ��ɾ����
		/* ����ƫ��2MB���ⲿFlash�ļ�ϵͳ�ռ����SPI Flash����6MB�ռ� */
		sector += 512;
		//һ��Ҫ�Ȳ�����д��
		SPI_FLASH_SectorErase(sector*4096);
		SPI_FLASH_BufferWrite((u8 *)buff,sector*4096,count*4096);

		res = RES_OK;
	
		return res;


	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions     ��������                                          */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..)  ������������*/
	BYTE cmd,		/* Control code ������*/
	void *buff		/* Buffer to send/receive control data ����/���տ������ݵĻ�����*/
)
{
	DRESULT res;

	switch (pdrv) {
	case SD_CARD :

		// Process of the command for the ATA drive  ATA�����������

		return res;

	case SPI_FLASH :
		

		// #��룬���˸�switch����ͬ����ʵ�ֲ�ͬ���ܰɡ�
		switch(cmd)
		{
			//������������
			case GET_SECTOR_COUNT:
				/* ����������1536*4096/1024/1024=6(MB) */
				*(DWORD*)buff = 1536;
				
			break;
			//����ÿ��������С
			case GET_SECTOR_SIZE:
				*(WORD*)buff = 4096;

			break;
			//���ز�����������С��������λΪ������
			case GET_BLOCK_SIZE:
			 *(WORD*)buff = 1;
			
			break;
			
		}		
			

		// Process of the command for the MMC/SD card  MMC/SD �������
		res = RES_OK;
		return res;

	}

	return RES_PARERR;
}
#endif

//����ʱ��
DWORD get_fattime (void)
{

	return 0;
}
