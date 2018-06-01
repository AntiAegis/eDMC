/*
 *	File		:	EDMC.WIFI.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of WiFi
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.WIFI.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	WIFI_MODULE				UART3
#define	WIFI_INT				INT_UART3
#define	WIFI_PORT_DATA			GPIO_PORT_A
#define	WIFI_PORT_CTL			GPIO_PORT_D
#define	WIFI_PIN_TX				GPIO_PIN_5
#define	WIFI_PIN_RX				GPIO_PIN_4
#define	WIFI_PIN_RST			GPIO_PIN_7
#define	WIFI_PIN_EN				GPIO_PIN_6

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
 *	Output		:	Status of setup
 *	Description	:	Setup WIFI at the first time of function called
 */
uint32_t	edmcWifiEnable(void)
{
	/* Static */
	static	bool isFstEn = true;
	
	/* GPIO setup */
	gpioOutputSetup(WIFI_PORT_CTL, WIFI_PIN_EN | WIFI_PIN_RST);
	
	/* UART setup */
	if(isFstEn)
	{
		uartSetup(ui32ClkFreq, WIFI_MODULE, 115200, UART_INT_OFF);
		isFstEn = false;
	}
	else	UARTEnable(WIFI_MODULE);
	
	/* WiFi setup */
	 
	/* Notify */
	edmcIdcNotify("Wifi: Enabled\n");
	
	/* LED */
	edmcLedState(edmcLed_WIFI, 1);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcWifiDisable(void)
{
	/* Disable */
	UARTDisable(WIFI_MODULE);
	 
	/* Notify */
	edmcIdcNotify("Wifi: Disabled\n");
	
	/* LED */
	edmcLedState(edmcLed_WIFI, 0);
	
	/* Return */
	return 0;
}

