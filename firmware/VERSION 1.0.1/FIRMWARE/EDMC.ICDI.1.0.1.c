/*
 *	File		:	EDMC.ICDI.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of ICDI
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.ICDI.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	ICDI_MODULE			UART_ICDI
#define	ICDI_INT			INT_UART0
#define	ICDI_PORT			GPIO_PORT_A
#define	ICDI_PIN_TX			GPIO_PIN_1
#define	ICDI_PIN_RX			GPIO_PIN_0
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
 *	Description	:	Setup ICDI at the first time of function called
 */
uint32_t	edmcIcdiEnable(void)
{
	/* Static */
	static	bool isFstEn = true;
	
	/* Setup */
	if(isFstEn)
	{
		uartSetup(ui32ClkFreq, ICDI_MODULE, 115200, UART_INT_RT | UART_INT_RX);
		isFstEn = false;
	}
	else	UARTEnable(ICDI_MODULE);

	/* LED */
	edmcLedState(LED(ICDI), 1);

	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcIcdiDisable(void)
{
	/* Disable */
	UARTDisable(ICDI_MODULE);
	 
	/* Notify */
	edmcIdcNotify("ICDI: Disabled\n");

	/* LED */
	edmcLedState(LED(ICDI), 0);

	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	edmcIcdiSendSysInfo(void)
{
	edmcIcdiSendStr("\n\n--------------------------------------\n");
	edmcIcdiSendStr("|          STARTING SYSTEM           |\n");
	edmcIcdiSendStr("| Embedded Device-Managing Computer  |\n");
	edmcIcdiSendStr("| Core  : TM4CNCPDT                  |\n");
	edmcIcdiSendStr("| Kernel: Real-Time operating system |\n");
	edmcIcdiSendStr("--------------------------------------\n\n");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	EDMC_ICDI_ISR(void)
{
	/* Exit ISR */
	UARTIntClear(ICDI_MODULE, UART_INT_RT | UART_INT_RX);
	
	/* Echo */
	uartSendChar(ICDI_MODULE, uartGetChar(ICDI_MODULE));
}
