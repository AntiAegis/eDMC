/*
 *	File		:	SDCARD.1.0.1.h
 *	Date		:	31/12/2016
 *	Author		:	Nguyen Chinh Thuy
 *	Language	: 	C
 *	IDE			:	CCS7.0.0.00042
 *	Object		:	TIVAC1294NCPDT
 *	Version		:	1.0.1
 *	Description	:	Library of SD Card
 */
/**************************************************************************************************
 *	PRE-DEIFINITIONs
 *************************************************************************************************/
#ifndef SDCARD_1_0_1_H_
#define SDCARD_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* Producing Library */
#include "driverlib/sysctl.h"
#include "fatfs/src/ff.h"
#include "fatfs/src/diskio.h"

/* My Library */

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Length of data buffer */
#define	SDC_DATA_NUM		102

/* Number of bytes of Path */
#define	SDC_PATH_NUM		128

/* Get string from name */
#define	SDC_GET_STR(x)		(#x)


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
extern	FRESULT		varFresult;


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Mount Disk */
FRESULT
sdcMount		(uint8_t varVol);

//-------------------------------------------------------------------------------------------------
/* Directory */
FRESULT
sdcChangeDir	(char strPath[]);

//-------------------------------------------------------------------------------------------------
/* File */
FRESULT
sdcFileOpen		(char strFName[]);
FRESULT
sdcFileClose	(char strFName[]);
FRESULT
sdcFileRead		(uint8_t arrGetData[], uint16_t varLength);

//-------------------------------------------------------------------------------------------------
/* Notify */
const char*
sdcNotifyStr	(FRESULT iFResult);


#endif /* SDCARD_1_0_1_H_ */
