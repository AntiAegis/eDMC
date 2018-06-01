/*
 *	File		:	EDMC.OS.1.0.1.h
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of this Operating System
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	EDMC_OS_1_0_1_H_
#define	EDMC_OS_1_0_1_H_


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
#include "cmsis_os.h"

/* My */

/* This project */



/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Signals */
#define	SWI_KP_PASS_PRC		1					// Keypad: Password process
#define	SWI_CMD_LINE		2					// Command Line
//-------------------------------------------------------------------------------------------------
/* Register ThreadID, MessageID, Event at here */
extern	osThreadId			osIDKpPassPrc;		// Keypad Password process
extern	osMessageQId		osMessIdKpPassPrc;
extern	osEvent				osMessEvKpPassPrc;
extern	osThreadId 			osIdLcdDraw;		// LCD draw
extern	osThreadId 			osIdKbUPdate;		// Keyboard update
extern	osThreadId			osIdCmdLine;		// Command line
extern	osMessageQId		osMessIdCmdLine;
extern	osEvent				osMessEvCmdLine;
extern	osThreadId 			osIdStartup;		// Startup
//-------------------------------------------------------------------------------------------------
/* Get priority */
#define	osPrior(x)			(osPriority##x)
//-------------------------------------------------------------------------------------------------
/* Setup */
uint32_t
edmcOsSetup	(void);


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Thread functions */
static 	void
osKpSweep	(void const *argument);
static	void
osKpPassPrc	(void const *argument);
static 	void
osLcdDraw	(void const *argument);
static 	void
osKbUpdate	(void const *argument);
static 	void
osCmdLine	(void const *argument);
static 	void
osStartup	(void const *argument);


#endif	/* EDMC_OS_1_0_1_H_ */

