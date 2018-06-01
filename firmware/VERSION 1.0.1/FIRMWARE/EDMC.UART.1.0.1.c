/*
 *	File		:	EDMC.UART.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of UART
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.UART.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	UART_MODULE			UART2
#define	UART_INT			INT_UART2
#define	UART_PORT			GPIO_PORT_A
#define	UART_PIN_TX			GPIO_PIN_7
#define	UART_PIN_RX			GPIO_PIN_6
//-------------------------------------------------------------------------------------------------
/* Register state */
typedef struct
{
	uint32_t	ui32Baud;	// Baudrate
	uint8_t		ui8Len;		// Length of word
	uint8_t		ui8Stop;	// Number of bytes of Stopbit
	uint8_t		ui8Par;		// Parity
	bool		isRec;		// Rececive or not?
}
tRegState;

static	tRegState	st_sRegState = 		// Regsiter State
{
	115200,
	UART_CONFIG_WLEN_8,
	UART_CONFIG_STOP_ONE,
	UART_CONFIG_PAR_NONE,
	false
};

#define	CONFIG(x)	(UART_CONFIG_##x)	// Get UART config name
#define	tCChar		const char
#define	NAME2STR(x)	(#x)				// Get string of name
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
#define	LEN_NAME_OFFSET		17

static	bool	lenEncode(char str[], uint8_t* pui8Len)
{
	if(!strcmp(str, &NAME2STR((CONFIG(WLEN_8)))[LEN_NAME_OFFSET]))
	{
		*pui8Len = CONFIG(WLEN_8);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(WLEN_7)))[LEN_NAME_OFFSET]))
	{
		*pui8Len = CONFIG(WLEN_7);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(WLEN_6)))[LEN_NAME_OFFSET]))
	{
		*pui8Len = CONFIG(WLEN_6);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(WLEN_5)))[LEN_NAME_OFFSET]))
	{
		*pui8Len = CONFIG(WLEN_5);
		return true;
	}
	
	/* Return */
	return false;
}
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
#define	STOP_NAME_OFFSET	17

static	bool	stopEncode(char str[], uint8_t* pui8Stop)
{
	if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(STOP_ONE)))[STOP_NAME_OFFSET]))
	{
		*pui8Stop = CONFIG(STOP_ONE);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(STOP_TWO)))[STOP_NAME_OFFSET]))
	{
		*pui8Stop = CONFIG(STOP_TWO);
		return true;
	}
	
	/* Return */
	return false;
}
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
#define	PAR_NAME_OFFSET		16

static	bool	parEncode(char str[], uint8_t* pui8Par)
{
	if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(PAR_NONE)))[PAR_NAME_OFFSET]))
	{
		*pui8Par = CONFIG(PAR_NONE);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(PAR_EVEN)))[PAR_NAME_OFFSET]))
	{
		*pui8Par = CONFIG(PAR_EVEN);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(PAR_ODD)))[PAR_NAME_OFFSET]))
	{
		*pui8Par = CONFIG(PAR_ODD);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(PAR_ONE)))[PAR_NAME_OFFSET]))
	{
		*pui8Par = CONFIG(PAR_ONE);
		return true;
	}
	else if(!strcmp((tCChar*)str, (tCChar*)&NAME2STR((CONFIG(PAR_ZERO)))[PAR_NAME_OFFSET]))
	{
		*pui8Par = CONFIG(PAR_ZERO);
		return true;
	}
	
	/* Return */
	return false;
}
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	bool	lenDecode(uint8_t ui8Len, char str[])
{
	/* Process */
	switch(ui8Len)
	{
		case CONFIG(WLEN_8):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(WLEN_8)))[LEN_NAME_OFFSET]);
			return true;
		case CONFIG(WLEN_7):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(WLEN_7)))[LEN_NAME_OFFSET]);
			return true;
		case CONFIG(WLEN_6):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(WLEN_6)))[LEN_NAME_OFFSET]);
			return true;
		case CONFIG(WLEN_5):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(WLEN_5)))[LEN_NAME_OFFSET]);
			return true;
	}
	
	/* Return */
	return false;
}
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	bool	stopDecode(uint8_t ui8Stop, char str[])
{
	/* Process */
	switch(ui8Stop)
	{
		case CONFIG(STOP_ONE):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(STOP_ONE)))[STOP_NAME_OFFSET]);
			return true;
		case CONFIG(STOP_TWO):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(STOP_TWO)))[STOP_NAME_OFFSET]);
			return true;
	}
	
	/* Return */
	return false;
}
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	bool	parDecode(uint8_t ui8Par, char str[])
{
	/* Process */
	switch(ui8Par)
	{
		case CONFIG(PAR_NONE):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(PAR_NONE)))[PAR_NAME_OFFSET]);
			return true;
		case CONFIG(PAR_ODD):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(PAR_ODD)))[PAR_NAME_OFFSET]);
			return true;
		case CONFIG(PAR_EVEN):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(PAR_EVEN)))[PAR_NAME_OFFSET]);
			return true;
		case CONFIG(PAR_ONE):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(PAR_ONE)))[PAR_NAME_OFFSET]);
			return true;
		case CONFIG(PAR_ZERO):
			strcpy(str, (tCChar*)&NAME2STR((CONFIG(PAR_ZERO)))[PAR_NAME_OFFSET]);
			return true;
	}
	
	/* Return */
	return false;
}
//-------------------------------------------------------------------------------------------------
/* Buffer */
#define	UART_BUFF_LEN		256								// Length of buffer
static	uint8_t				st_pui8Buff[UART_BUFF_LEN];		// Buffer
static	uint8_t				st_ui8BuffCount = 255;			// Count byte of buffer
//static	bool				st_isOvf = false;				// Flag overflow

#define	buffClr				memset(st_pui8Buff, 0, UART_BUFF_LEN)	// Clear buffer
//-------------------------------------------------------------------------------------------------
/* Send */
#define	uartSend(x) 		uartSendStr(UART_MODULE, x)


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/*
 *	Input		:	None
 *	Output		:	Status of setup
 *	Description	:	Enable UART module
 */
uint32_t	edmcUartEnable(void)
{
	/* Indicate whether the first time to be enabled */
	static	bool	isFstEn = true;
	
	/* The first time to be enabled */
	if(isFstEn)
	{
		uartSetup(ui32ClkFreq, UART_MODULE, 115200, UART_INT_OFF);
		isFstEn = false;
	}
	
	/* Not the first time to be enabled */
	else	UARTEnable(UART_MODULE);
	 
	/* Notify */
	edmcIdcNotify("UART: Enabled\n");

	/* LED */
	edmcLedState(edmcLed_UART, 1);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Status of setup
 *	Description	:	Disable UART module
 */
uint32_t	edmcUartDisable(void)
{
	/* Disable */
	UARTDisable(UART_MODULE);
	 
	/* Notify */
	edmcIdcNotify("UART: Disabled\n");

	/* LED */
	edmcLedState(edmcLed_UART, 0);
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
uint32_t	edmcUartConfig(char strType[], char str[])
{
	/* Declare */
	uint8_t	ui8Tmp;
	
	/* Baudrate */
	if(!strcmp(strType, "baud"))
	{
		st_sRegState.ui32Baud = atol((tCChar*)str);
		UARTDisable(UART_MODULE);
		UARTConfigSetExpClk(UART_MODULE, ui32ClkFreq, st_sRegState.ui32Baud,
							(uint32_t)st_sRegState.ui8Len  |
							(uint32_t)st_sRegState.ui8Stop |
							(uint32_t)st_sRegState.ui8Par);
		UARTEnable(UART_MODULE);
	}
	
	/* Length */
	else if(!strcmp(strType, "len"))
	{
		if(lenEncode(str, &ui8Tmp))
		{
			st_sRegState.ui8Len = ui8Tmp;
			UARTDisable(UART_MODULE);
			UARTConfigSetExpClk(UART_MODULE, ui32ClkFreq, st_sRegState.ui32Baud,
								(uint32_t)st_sRegState.ui8Len  |
								(uint32_t)st_sRegState.ui8Stop |
								(uint32_t)st_sRegState.ui8Par);
			UARTEnable(UART_MODULE);
		}
		else
		{
			/* NEED CODE AT HERE */
		}
	}
	
	/* Stopbit */
	else if(!strcmp(strType, "stop"))
	{
		if(stopEncode(str, &ui8Tmp))
		{
			st_sRegState.ui8Stop = ui8Tmp;
			UARTDisable(UART_MODULE);
			UARTConfigSetExpClk(UART_MODULE, ui32ClkFreq, st_sRegState.ui32Baud,
								(uint32_t)st_sRegState.ui8Len  |
								(uint32_t)st_sRegState.ui8Stop |
								(uint32_t)st_sRegState.ui8Par);
			UARTEnable(UART_MODULE);
		}
		else
		{
			/* NEED CODE AT HERE */
		}
	}
	
	/* Parity */
	else if(!strcmp(strType, "par"))
	{
		if(parEncode(str, &ui8Tmp))
		{
			st_sRegState.ui8Par = ui8Tmp;
			UARTDisable(UART_MODULE);
			UARTConfigSetExpClk(UART_MODULE, ui32ClkFreq, st_sRegState.ui32Baud,
								(uint32_t)st_sRegState.ui8Len  |
								(uint32_t)st_sRegState.ui8Stop |
								(uint32_t)st_sRegState.ui8Par);
			UARTEnable(UART_MODULE);
		}
		else
		{
			/* NEED CODE AT HERE */
		}
	}
	
	/* Receive */
	else if(!strcmp(strType, "rec"))
	{
		if(!strcmp(str, "0"))
		{
			st_sRegState.isRec = false;
			UARTIntDisable(UART_MODULE, UART_INT_RX);
		}
		else if(!strcmp(str, "1"))
		{
			st_sRegState.isRec = true;
			IntMasterEnable();
			IntEnable(UART_INT);
			UARTIntEnable(UART_MODULE, UART_INT_RX);
		}
		else
		{
			/* NEED CODE AT HERE */
		}
	}
	
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	edmcUartStatus(void)
{
	/* Declare */
	char str[10];
	
	/* Process and print */
	edmcIdcNotify("\n\nUART module status:\n");
	
		edmcIdcNotify("->Baudrate : %u\n", st_sRegState.ui32Baud);
	
	if(lenDecode(st_sRegState.ui8Len, str))
		edmcIdcNotify("->Length   : %s\n", str);
	
	if(stopDecode(st_sRegState.ui8Stop, str))
		edmcIdcNotify("->Stopbit  : %s\n", str);
	
	if(parDecode(st_sRegState.ui8Par, str))
		edmcIdcNotify("->Parity   : %s\n", str);
	
	if(st_sRegState.isRec)
		edmcIdcNotify("->Receive  : true\n");
	else
		edmcIdcNotify("->Receive  : false\n");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
bool	edmcBuffPrint(uint8_t ui8Start, uint8_t ui8Num, char strFormat)
{
	/* Declare */
	uint8_t	i;
	uint8_t length;
	
	/* Verify */
	if((ui8Start + ui8Num) > UART_BUFF_LEN)	return false;
	else 	length = ui8Start + ui8Num;

	/* Char format */
	if(strFormat == 'c')
		for(i = ui8Start; i < length; i++) edmcIdcNotify("%c", st_pui8Buff[i]);

	/* Dec format */
	else if(strFormat == 'd')
		for(i = ui8Start; i < length; i++) edmcIdcNotify("[%d]: %d\n", i, st_pui8Buff[i]);

	/* Bin format */
	else if(strFormat == 'b')
		for(i = ui8Start; i < length; i++)
		{
			edmcIdcNotify("[%d]: ", i);
			edmcIdcBin((uint32_t)st_pui8Buff[i]);
			edmcIdcNotify("\n");
		}

	/* Hex format */
	else if(strFormat == 'x')
		for(i = ui8Start; i < length; i++) edmcIdcNotify("[%d]: %x\n", i, st_pui8Buff[i]);

	/* Return */
	return true;
}

//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void
edmcUartSend(char str[], uint32_t ui32Time, uint32_t ui32Delay)
{
	while(ui32Time--)
	{
		uartSend(str);
		
		/* NEED SOLUTION FOR DELAY */
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	EDMC_UART_ISR(void)
{
	/* Exit */
	UARTIntClear(UART_MODULE, UART_INT_RX);

	/* Store to buffer */
    while(HWREG(UART_MODULE + UART_O_FR) & UART_FR_RXFE);
	st_pui8Buff[++st_ui8BuffCount] = HWREG(UART_MODULE + UART_O_DR);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */

