/*
 *	File		:	EDMC.LED.1.0.1.h
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of LED
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	EDMC_LED_1_0_1_H_
#define	EDMC_LED_1_0_1_H_


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
#include "LAUNCHPAD.1.0.1.h"
#include "GPIO.1.0.1.h"

/* This project */
#include "EDMC.INDICATOR.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* LEDs */
typedef enum
{
	edmcLed_KP 		= 0,
	edmcLed_LCD 	= 1,
	edmcLed_KB 		= 2,
	edmcLed_SDC 	= 3,
	edmcLed_ICDI 	= 4,
	edmcLed_UART 	= 5,
	edmcLed_SPI 	= 6,
	edmcLed_I2C 	= 7,
	edmcLed_WIFI 	= 8,
	edmcLed_BUZZ 	= 9
} tLed;

#define	LED(x)	(edmcLed_##x)		// Get name of LED
//-------------------------------------------------------------------------------------------------
/* Setup */
uint32_t
edmcLedSetup	(void);
//-------------------------------------------------------------------------------------------------
/* State of LED */
void
edmcLedState	(tLed ui8Led, bool state);


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Led state */
static	void
ledState		(uint32_t port, uint8_t pin, bool state); 


#endif	/* EDMC_LED_1_0_1_H_ */

