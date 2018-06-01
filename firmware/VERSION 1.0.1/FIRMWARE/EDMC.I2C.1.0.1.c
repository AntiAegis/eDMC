/*
 *	File		:	EDMC.I2C.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of I2C
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.I2C.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	I2C_MODULE				I2C_MODULE_1
#define	I2C_INT					INT_I2C1
#define	I2C_PORT				GPIO_PORT_G
#define	I2C_PIN_SDA				GPIO_PIN_1
#define	I2C_PIN_SCL				GPIO_PIN_0

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
 *	Description	:	Enable I2C
 */
uint32_t	edmcI2cEnable(void)
{
	/* Static */
	static	bool	isFstEn = true;
	
	/* Enable */
	if(isFstEn)
	{
		i2cMstSetup(I2C_MODULE, ui32ClkFreq, I2C_RATE_400_KBPS);
		isFstEn = false;
	}
	else	I2CMasterEnable(I2C_MODULE);
	 
	/* Notify */
	edmcIdcNotify("I2C: Enabled\n");

	/* LED */
	edmcLedState(LED(I2C), 1);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Status of setup
 *	Description	:	Disable I2C
 */
uint32_t	edmcI2cDisable(void)
{
	/* Disable */
	I2CMasterDisable(I2C_MODULE);
	 
	/* Notify */
	edmcIdcNotify("I2C: Disabled\n");

	/* LED */
	edmcLedState(LED(I2C), 0);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */

