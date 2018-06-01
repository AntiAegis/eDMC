/*
 *	Date		:	2017/01/27
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of Command Line
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	SW_CMD_1_0_1_H_
#define	SW_CMD_1_0_1_H_


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


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Program Respond */
typedef enum
{
	PROG_RES_OK_CMD 			= 0,
	PROG_RES_NULL_CMD			= 1,
	PROG_RES_INVALID_CMD 		= 2,
	PROG_RES_INVALID_PARA 		= 3,
	PROG_RES_CANNOT_RUN_CMD 	= 4,
	PROG_RES_CHANGE_SOFTWARE	= 5,
}
etProgRes;

#define	PROG_RES(x)		(PROG_RES_##x)	// Get name of enum Program Respond
//-------------------------------------------------------------------------------------------------
/* Program Address */
typedef struct
{
	const char	strProg[11];
	etProgRes 	(*pfn)(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum);
}
tProgAddr;
//-------------------------------------------------------------------------------------------------
/* Process command string */
void
swCmdStrPrc	(char str[]);
//-------------------------------------------------------------------------------------------------
/* Argument list */
uint8_t
swCmdArgList(char str[], uint8_t* pui8ArgPos);


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Find Program */
static	bool
findProg	(char str[], uint8_t* pui8Prog);
/* Result analysis */
static	void
resAnalysis	(etProgRes PROG_RES);


#endif	/* SW_CMD_1_0_1_H_ */

