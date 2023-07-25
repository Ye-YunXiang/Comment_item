/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*        FATFS 模块的整数类型定义            */
/*-------------------------------------------*/

#ifndef _FF_INTEGER
#define _FF_INTEGER

#ifdef _WIN32	/* Development platform  开发平台*/

#include <windows.h>
#include <tchar.h>      // 通用编码字符，tchar可以用于双字节字符串，使程序可以用于中日韩等国语言文字处理、显示。

#else			/* Embedded platform 嵌入式平台*/

/* This type MUST be 8-bit  该类型为 8-bit*/
typedef unsigned char	BYTE;

/* These types MUST be 16-bit */
typedef short			SHORT;
typedef unsigned short	WORD;
typedef unsigned short	WCHAR;

/* These types MUST be 16-bit or 32-bit  这些类型必须是 16-bit 或 32-bit*/
typedef int				INT;
typedef unsigned int	UINT;

/* These types MUST be 32-bit */
typedef long			LONG;
typedef unsigned long	DWORD;

#endif

#endif
