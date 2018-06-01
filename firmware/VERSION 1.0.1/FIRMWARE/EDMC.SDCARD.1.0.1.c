/*
 *	File				:	EDMC.SDCARD.1.0.1.c
 *	Date				:	2017/01/10
 *	Author			:	Nguyen Chinh Thuy
 *	Version			:	1.0.1
 *	Description	:	Source file of SD Card
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.SDCARD.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	SDC_MODULE				SSI_MODULE_2
#define	SDC_PORT				GPIO_PORT_D
#define	SDC_PIN_SCK				GPIO_PIN_3
#define	SDC_PIN_CS				GPIO_PIN_2
#define	SDC_PIN_MOSI			GPIO_PIN_1
#define	SDC_PIN_MISO			GPIO_PIN_0

//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/*
 *	Input		:	None
 *	Output		:	Status of Setup
 *	Description	:	Setup SD Card
 */
uint32_t	edmcSdcEnable(void)
{
	/* Setup */
//	sdcMount(0);
//	varFresult = sdcFileOpen("eDMC.txt");
//	if(varFresult)
//	{
//		edmcIdcNotify("SD Card: ");
//		edmcIdcNotify((char*)sdcNotifyStr(varFresult));
//		edmcIdcNotify("\n");
//		return 1;
//	}
//	else	sdcFileClose("eDMC.txt");
	 
	/* Notify */
	edmcIdcNotify("SD Card: Enabled\n");
	
	/* LED */
	edmcLedState(LED(SDC), 1);
	 
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcSdcDisable(void)
{
	/*  */
	 
	/* Notify */
	edmcIdcNotify("SD Card: Disabled\n");
	
	/* LED */
	edmcLedState(LED(SDC), 0);
	 
	/* Return */
	return 0;
}

