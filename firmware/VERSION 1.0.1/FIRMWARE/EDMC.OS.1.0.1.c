/*
 *	File		:	EDMC.OS.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of Operating System
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.OS.1.0.1.h"
#include "EDMC.LED.1.0.1.h"
#include "EDMC.KEYPAD.1.0.1.h"
#include "EDMC.LCD.1.0.1.h"
#include "EDMC.KEYBOARD.1.0.1.h"
#include "EDMC.SDCARD.1.0.1.h"
#include "EDMC.ICDI.1.0.1.h"
#include "EDMC.UART.1.0.1.h"
#include "EDMC.SPI.1.0.1.h"
#include "EDMC.I2C.1.0.1.h"
#include "EDMC.WIFI.1.0.1.h"
#include "EDMC.INDICATOR.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Keypad Sweep */
static				osThreadDef(osKpSweep, osPriorityNormal,1, 0);
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	void	osKpSweep(void const *argument)
{
	while(1)
	{
		edmcKpSweep();
		osDelay(50);
	}
}
//-------------------------------------------------------------------------------------------------
/* LCD Draw */
static				osThreadDef(osLcdDraw, osPriorityNormal, 1, 0);
static	osThreadId 	osIdLcdDraw;
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	void	osLcdDraw(void const *argument)
{
	while(1)
	{
		gpioLEDState(1, 2);
		osDelay(500);
	}
}
//-------------------------------------------------------------------------------------------------
/* Keypad: Password Process */
static					osThreadDef(osKpPassPrc, osPriorityAboveNormal, 1, 0);
		osThreadId		osIDKpPassPrc;
static					osMessageQDef(osMessKpPassPrc, 1, uint8_t);
		osMessageQId	osMessIdKpPassPrc;
static	osEvent			osMessEvKpPassPrc;
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	void	osKpPassPrc(void const *argument)
{
	/* Execute */
	while(1)
	{
		osSignalWait(SWI_KP_PASS_PRC, osWaitForever);
		osMessEvKpPassPrc = osMessageGet(osMessIdKpPassPrc, 0);
		edmcKpPassPrc((tKpBtn)osMessEvKpPassPrc.value.v);
		osSignalClear(osIDKpPassPrc, SWI_KP_PASS_PRC);
	}
}
//-------------------------------------------------------------------------------------------------
/* Keyboard Update */
static				osThreadDef(osKbUpdate, osPriorityNormal, 1, 0);
static	osThreadId 	osIdKbUPdate;
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	void	osKbUpdate(void const *argument)
{
	while(1)
	{
		edmcKbUpdate();
	}
}
//-------------------------------------------------------------------------------------------------
/* Command Line */
static					osThreadDef(osCmdLine, osPriorityAboveNormal, 1, 0);
		osThreadId 		osIdCmdLine;
static					osMessageQDef(osMessCmdLine, 1, uint8_t);
		osMessageQId	osMessIdCmdLine;
		osEvent			osMessEvCmdLine;
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	 void	osCmdLine(void const *argument)
{
	/* Process */
	while(1)
	{
		osSignalWait(SWI_CMD_LINE, osWaitForever);
		osMessEvCmdLine = osMessageGet(osMessIdCmdLine, 0);
		usbStr((uint8_t)osMessEvCmdLine.value.v);
		osSignalClear(osIdCmdLine, SWI_CMD_LINE);
	}
}
//-------------------------------------------------------------------------------------------------
/* Startup */
static				osThreadDef(osStartup, osPriorityNormal, 1, 0);
static	osThreadId 	osIdStartup;
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	 void	osStartup(void const *argument)
{
	while(1)
	{
		if(edmcKpPassIsRight())
		{
			edmcKpPassDisable();
			osThreadTerminate(osIDKpPassPrc);

			edmcKbEnable();
			osIdKbUPdate = osThreadCreate(osThread(osKbUpdate), NULL);

			osIdCmdLine	= osThreadCreate(osThread(osCmdLine), NULL);
			osMessIdCmdLine = osMessageCreate(osMessageQ(osMessCmdLine), NULL);
			edmcIdcNotify("Command Line: Enabled\n");
			
			osThreadTerminate(osIdStartup);
		}
	}
}


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/*
 *	Input		:	None
 *	Output		:	State of Setup
 *	Description	:	Setup Operating system
 */
uint32_t	edmcOsSetup(void)
{
	/* Notify */
	edmcIdcNotify("OS: Enabled\n");
	
	/* Create threads */
	osIdStartup		= osThreadCreate(osThread(osStartup)	, NULL);
					  osThreadCreate(osThread(osKpSweep)	, NULL);
	osIDKpPassPrc	= osThreadCreate(osThread(osKpPassPrc)	, NULL);
	osIdLcdDraw		= osThreadCreate(osThread(osLcdDraw)	, NULL);

	/* Create message */
	osMessIdKpPassPrc = osMessageCreate(osMessageQ(osMessKpPassPrc)	, NULL);

	/* Start kernel */
	osKernelStart();

	/* Wait forever */
	osDelay(osWaitForever);

	/* Return */
	return 0;
}

