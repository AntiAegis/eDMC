/*
 *	File			:	EDMC.SSI.1.0.1.c
 *	Date created	:	28/12/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Source file for SSI
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "SSI.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
bool
ssiSetup(uint32_t SSI_MODULE_, uint32_t varClkFreq, uint32_t SSI_PROTO_, uint32_t SSI_MODE_,
														uint32_t varBitRate, uint8_t varDataWidth)
{
	/* Check varBitRate and varDataWidth */
	if(varBitRate > 2000000)					return false;
	if(varDataWidth < 8 || varDataWidth > 16)	return false;

	/* Enable peripheral */
	ssiEnableModule(SSI_MODULE_);

	/* Config mux in GPIO */
	ssiMuxGPIO(SSI_MODULE_);

	/* Config SSI */
	SSIConfigSetExpClk(SSI_MODULE_, varClkFreq, SSI_PROTO_, SSI_MODE_, varBitRate, varDataWidth);

	/* Enable SSI module */
	SSIEnable(SSI_MODULE_);

	/* Return */
	return true;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
ssiEnableModule(uint32_t SSI_MODULE_)
{
	/* Declare */
	uint32_t varPeriph = 0;

	/* Indicate peripheral */
	switch (SSI_MODULE_)
	{
		case SSI_MODULE_0: varPeriph = SYSCTL_PERIPH_SSI0; break;
		case SSI_MODULE_1: varPeriph = SYSCTL_PERIPH_SSI1; break;
		case SSI_MODULE_2: varPeriph = SYSCTL_PERIPH_SSI2; break;
		case SSI_MODULE_3: varPeriph = SYSCTL_PERIPH_SSI3; break;
	}

	/* Enable peripheral */
	SysCtlPeripheralEnable(varPeriph);

	/* Wait for peripheral ready */
	while(!SysCtlPeripheralReady(varPeriph));
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	ssiMuxGPIO
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
ssiMuxGPIO(uint32_t SSI_MODULE_)
{
	/* Config Mux for GPIO */
	switch (SSI_MODULE_)
	{
		case SSI_MODULE_0:
			gpioEnablePort(GPIO_PORT_A);			// Port
			GPIOPinConfigure(GPIO_PA2_SSI0CLK);		// CLK
			GPIOPinConfigure(GPIO_PA3_SSI0FSS);		// FSS
			GPIOPinConfigure(GPIO_PA4_SSI0XDAT0);	// TX
			GPIOPinConfigure(GPIO_PA5_SSI0XDAT1);	// RX
			GPIOPinTypeSSI(GPIO_PORT_A, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);
			break;
		case SSI_MODULE_1:
			gpioEnablePort(GPIO_PORT_B);			// Port
			GPIOPinConfigure(GPIO_PB5_SSI1CLK);		// CLK
			GPIOPinConfigure(GPIO_PB4_SSI1FSS);		// FSS
			GPIOPinTypeSSI(GPIO_PORT_B, GPIO_PIN_5 | GPIO_PIN_4);
			gpioEnablePort(GPIO_PORT_E);			// Port
			GPIOPinConfigure(GPIO_PE4_SSI1XDAT0);	// TX
			GPIOPinConfigure(GPIO_PE5_SSI1XDAT1);	// RX
			GPIOPinTypeSSI(GPIO_PORT_E, GPIO_PIN_4 | GPIO_PIN_5);
			break;
		case SSI_MODULE_2:
			gpioEnablePort(GPIO_PORT_D);			// Port
			GPIOPinConfigure(GPIO_PD3_SSI2CLK);		// CLK
			GPIOPinConfigure(GPIO_PD2_SSI2FSS);		// FSS
			GPIOPinConfigure(GPIO_PD1_SSI2XDAT0);	// TX
			GPIOPinConfigure(GPIO_PD0_SSI2XDAT1);	// RX
			GPIOPinTypeSSI(GPIO_PORT_D, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0);
			break;
		case SSI_MODULE_3:
			gpioEnablePort(GPIO_PORT_Q);			// Port
			GPIOPinConfigure(GPIO_PQ0_SSI3CLK);		// CLK
			GPIOPinConfigure(GPIO_PQ1_SSI3FSS);		// FSS
			GPIOPinConfigure(GPIO_PQ2_SSI3XDAT0);	// TX
			GPIOPinConfigure(GPIO_PQ3_SSI3XDAT1);	// RX
			GPIOPinTypeSSI(GPIO_PORT_Q, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
			break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	ssiIntSetup
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
ssiIntSetup(uint32_t SSI_MODULE_, uint32_t SSI_INT_, void (*pfnHandler)(void))
{
	/* Enable Master interrupt */
	IntMasterEnable();

	/* Enable interrupt of UART */
	switch (SSI_MODULE_)
	{
		case SSI_MODULE_0:
			IntEnable(INT_SSI0); break;
		case SSI_MODULE_1:
			IntEnable(INT_SSI1); break;
		case SSI_MODULE_2:
			IntEnable(INT_SSI2); break;
		case SSI_MODULE_3:
			IntEnable(INT_SSI3); break;
	}

	/* Register interrupt */
	SSIIntRegister(SSI_MODULE_, pfnHandler);

	/* Enable interrupt source */
	SSIIntEnable(SSI_MODULE_, SSI_INT_);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
ssiSendChar(uint32_t SSI_MODULE_, uint8_t varData)
{
	SSIDataPut(SSI_MODULE_, varData);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
ssiSendStr(uint32_t SSI_MODULE_, uint8_t arrData[], uint16_t varLength)
{
	/* Declare */
	uint16_t i;

	/* Loop to send */
	for(i = 0; i < varLength; i++) ssiSendChar(SSI_MODULE_, arrData[i]);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
uint32_t
ssiGetChar(uint32_t SSI_MODULE_)
{
	/* Declare */
	uint32_t varBuff;

	/* Wait for idle */
	while(SSIBusy(SSI_MODULE_));

	/* Get data */
	SSIDataGet(SSI_MODULE_, &varBuff);

	/* Return */
	return varBuff;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
void
ssiGetStr(uint32_t SSI_MODULE_, uint32_t arrData[])
{
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF SSI.1.0.1.c
 *************************************************************************************************/
