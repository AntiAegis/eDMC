/*
 *	File		:	EDMC.LCD.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of LCD
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.LCD.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	LCD_PORT				GPIO_PORT_B
#define	LCD_PIN_R				GPIO_PIN_4
#define	LCD_PIN_G				GPIO_PIN_3
#define	LCD_PIN_B				GPIO_PIN_2
#define	LCD_PIN_HS				GPIO_PIN_1
#define	LCD_PIN_VS				GPIO_PIN_0
#define	LCD_PIN_SIG				(LCD_PIN_R | LCD_PIN_G | LCD_PIN_B)
#define	LCD_PIN_SYNC			(LCD_PIN_HS | LCD_PIN_VS)
#define	LCD_PIN					(LCD_PIN_SIG | LCD_PIN_SYNC)

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
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcLcdEnable(void)
{
	/* Setup GPIO pins */
	gpioOutputSetup(LCD_PORT, LCD_PIN);
	
	/* Notify */
	 edmcIdcNotify("LCD: Enabled\n");
	
	/* LED */
	edmcLedState(LED(LCD), 1);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcLcdDisable(void)
{
	/*  */
	 
	/* Notify */
	edmcIdcNotify("LCD: Disabled\n");
	
	/* LED */
	edmcLedState(LED(LCD), 0);
	
	/* Return */
	return 0;
}

