/*
 *	File		:	EDMC.KEYBOARD.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of Keyboard
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.KEYBOARD.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/*  */
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
 *	Description	:	Setup keyboard
 */
uint32_t	edmcKbEnable(void)
{
	/* Setup */
	usbSetup();
	 
	/* Notify */
	edmcIdcNotify("Keyboard: Enabled\n");
	
	/* LED */
	edmcLedState(LED(KB), 1);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcKbDisable(void)
{
	/* Disable */
	USBHostPwrDisable(USB0_BASE);
	 
	/* Notify */
	edmcIdcNotify("Keyboard: Disabled\n");
	
	/* LED */
	edmcLedState(LED(KB), 0);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------

