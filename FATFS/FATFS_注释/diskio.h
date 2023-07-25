/*-----------------------------------------------------------------------/
/  Low level disk interface modlue include file   (C)ChaN, 2014          /
/-----------------------------------------------------------------------*/
// �ͼ�Ӳ�̽ӿ�ģ��

#ifndef _DISKIO_DEFINED
#define _DISKIO_DEFINED

#ifdef __cplusplus
extern "C" {
#endif

#define _USE_WRITE	1	/* 1: Enable disk_write function ����disk_write ����*/
#define _USE_IOCTL	1	/* 1: Enable disk_ioctl fucntion ���� disk_ioctl ����*/

#include "integer.h"		// C++����������


/* Status of Disk Functions 	Ӳ�̹���״̬*/
typedef BYTE	DSTATUS;

/* Results of Disk Functions  ���̺������ */
typedef enum {
	RES_OK = 0,		/* 0: Successful  �ɹ�*/
	RES_ERROR,		/* 1: R/W Error  ����*/
	RES_WRPRT,		/* 2: Write Protected д�뱣�� */
	RES_NOTRDY,		/* 3: Not Ready  û��׼����*/
	RES_PARERR		/* 4: Invalid Parameter  ��Ч�Ĳ���*/
} DRESULT;


/*---------------------------------------*/
/* Prototypes for disk control functions */
// ���̿��ƺ���ԭ�ͣ����Ƿ���byte���͡�


DSTATUS disk_initialize (BYTE pdrv);		// ���̳�ʼ��
DSTATUS disk_status (BYTE pdrv);			// ����״̬
DRESULT disk_read (BYTE pdrv, BYTE* buff, DWORD sector, UINT count);	
DRESULT disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count);
DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);


/* Disk Status Bits (DSTATUS) ����״̬λ*/

#define STA_NOINIT		0x01	/* Drive not initialized  ����δ��ʼ��*/
#define STA_NODISK		0x02	/* No medium in the drive ��������û�н���*/
#define STA_PROTECT		0x04	/* Write protected д�뱣��*/


/* Command code for disk_ioctrl fucntion  disk_ioctrl�ĺ����������*/

/* Generic command (Used by FatFs) ͨ������*/
#define CTRL_SYNC			0	/* Complete pending write process ��ɹ����д����(needed at _FS_READONLY == 0) */
#define GET_SECTOR_COUNT	1	/* Get media size ��ȡý���С (needed at _USE_MKFS == 1) */
#define GET_SECTOR_SIZE		2	/* Get sector size ��ȡ������С(needed at _MAX_SS != _MIN_SS) */
#define GET_BLOCK_SIZE		3	/* Get erase block size ��ȡ������Ĵ�С (needed at _USE_MKFS == 1) */
#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used ֪ͨ�豸�������ϵ����ݲ��ڱ�ʹ�� (needed at _USE_TRIM == 1) */

/* Generic command (Not used by FatFs) */
#define CTRL_POWER			5	/* Get/Set power status ��ȡ/���� ��Դ״̬*/
#define CTRL_LOCK			6	/* Lock/Unlock media removal  ����/���� �����Ƴ�*/
#define CTRL_EJECT			7	/* Eject media ��������*/
#define CTRL_FORMAT			8	/* Create physical format on the media �ڽ����ϴ��������ʽ*/

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision ��ȡF/W�޸�*/
#define ATA_GET_MODEL		21	/* Get model name  ��ȡģ�͵�����*/
#define ATA_GET_SN			22	/* Get serial number ��ȡ���к�*/

#ifdef __cplusplus
}
#endif

#endif
