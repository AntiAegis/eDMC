/*
 *	Date		:	2017/01/27
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of System Control
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	SW_SYSCTL_1_0_1_H_
#define	SW_SYSCTL_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

/* Producer */

/* My */

/* This project */
#include "FIRMWARE/FIRMWARE.1.0.1.h"
#include "SOFTWARE/Command Line/SW.CMD.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Implementing function of SysCtl */
etProgRes
fnSysCtl	(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
//-------------------------------------------------------------------------------------------------
/* Command */
typedef struct
{
	char		strCmd[11];
	etProgRes	(*pfn)(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
}
tSysCtlCmd;
//-------------------------------------------------------------------------------------------------
/* Component */
typedef enum
{
	CPNT_STT_NOT_AVAI	= -1,
	CPNT_STT_IDLE		= 0,
	CPNT_STT_RUNNING	= 1,
}
etCpntStt;
#define	CPNT_STT(x)		(CPNT_STT_##x)
typedef struct
{
	bool		isEn;			// Enabled flag
	etCpntStt	STT;			// Status
	uint32_t	ui32Mem;		// Memory
}
tSysCtlCpnt;


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Command */
static	bool
findCmd		(char str[], uint8_t* pui8Index);
static	etProgRes
cmdHelp		(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
static	etProgRes
cmdEnable	(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
static	etProgRes
cmdDisable	(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
static	etProgRes
cmdInfo		(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
//-------------------------------------------------------------------------------------------------
/* Info */
static	void
infoPrint	(uint8_t IDX_);


#endif	/* SW_SYSCTL_1_0_1_H_ */

