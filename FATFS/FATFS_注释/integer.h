/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*        FATFS ģ����������Ͷ���            */
/*-------------------------------------------*/

#ifndef _FF_INTEGER
#define _FF_INTEGER

#ifdef _WIN32	/* Development platform  ����ƽ̨*/

#include <windows.h>
#include <tchar.h>      // ͨ�ñ����ַ���tchar��������˫�ֽ��ַ�����ʹ��������������պ��ȹ��������ִ�����ʾ��

#else			/* Embedded platform Ƕ��ʽƽ̨*/

/* This type MUST be 8-bit  ������Ϊ 8-bit*/
typedef unsigned char	BYTE;

/* These types MUST be 16-bit */
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types MUST be 16-bit or 32-bit  ��Щ���ͱ����� 16-bit �� 32-bit*/
typedef int				INT;
typedef unsigned int	UINT;

/* These types MUST be 32-bit */
typedef long			LONG;
typedef unsigned long	DWORD;

#endif

#endif
