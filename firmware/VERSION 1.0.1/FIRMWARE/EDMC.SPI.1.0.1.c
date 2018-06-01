/*
 *	File		:	EDMC.SPI.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of SPI
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.SPI.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	SPI_MODULE				SSI_MODULE_3
#define	SPI_INT					INT_SSI3
#define	SPI_PORT				GPIO_PORT_Q
#define	SPI_PIN_MISO			GPIO_PIN_3
#define	SPI_PIN_MOSI			GPIO_PIN_2
#define	SPI_PIN_CS				GPIO_PIN_1
#define	SPI_PIN_SCK				GPIO_PIN_0

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
 *	Description	:	Enable SPI (not be used in the first time of function called)
 */
uint32_t	edmcSpiEnable(void)
{
	/* Static */
	static	bool	isFstEn = true;
	
	/* Enable */
	if(isFstEn)
	{
		ssiSetup(SPI_MODULE, ui32ClkFreq, SSI_PROTO_MOTO_0, SSI_MODE_MASTER, 400000, 8);
		isFstEn = false;
	}
	else	SSIEnable(SPI_MODULE);
	 
	/* Notify */
	edmcIdcNotify("SPI: Enabled\n");

	/* LED */
	edmcLedState(LED(SPI), 1);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Status of setup
 *	Description	:	Disable SPI
 */
uint32_t	edmcSpiDisable(void)
{
	/* Disable */
	SSIDisable(SPI_MODULE);
	 
	/* Notify */
	edmcIdcNotify("SPI: Disabled\n");

	/* LED */
	edmcLedState(LED(SPI), 0);
	
	/* Return */
	return 0;
}

