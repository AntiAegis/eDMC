/*
 *	File			:	GLCD_12864.0.0.101.c
 *	Date created	:	30/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	0.0.101
 *	Description		:	Library of LCD Graphic 128x64
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */

/* Producing Library */

/* My Library */
#include "GLCD_12864.0.0.101.h"

/* This project */


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
 uint8_t	varCheck = 0;
 
 /**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Pins */
static	uint32_t		varGLCDPortControl;
static	uint32_t		varGLCDPortData;
static	uint32_t		varGLCDPinControl[4];	// RS, RW, EN, PSB


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	glcd12864PinSetup
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864PinSetup(uint32_t PortControl, uint32_t PinRS, uint32_t PinRW, uint32_t PinE,
																uint32_t PinPSB, uint32_t PortData)
{
	/* Control */
	varGLCDPortControl 		= PortControl;
	varGLCDPinControl[0] 	= PinRS;
	varGLCDPinControl[1] 	= PinRW;
	varGLCDPinControl[2] 	= PinE;
	varGLCDPinControl[3] 	= PinPSB;
	gpioOutputSetup(varGLCDPortControl, varGLCDPinControl[0] | varGLCDPinControl[1] |
													varGLCDPinControl[2] | varGLCDPinControl[3]);

	/* Data */
	varGLCDPortData = PortData;
	gpioOutputSetup(varGLCDPortData, 0xFF);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864CtlPinSetup
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864CtlPinSetup(uint8_t GLCD_CTL_)
{
	switch (GLCD_CTL_)
	{
		case GLCD_CTL_INSTRUCTION_WRITE:
			gpioLow(varGLCDPortControl, varGLCDPinControl[0] | varGLCDPinControl[1]);
			break;
		case GLCD_CTL_INSTRUCTION_READ:
			gpioLow(varGLCDPortControl, varGLCDPinControl[0]);
			gpioHigh(varGLCDPortControl, varGLCDPinControl[1]);
			break;
		case GLCD_CTL_DATA_WRITE:
			gpioHigh(varGLCDPortControl, varGLCDPinControl[0]);
			gpioLow(varGLCDPortControl, varGLCDPinControl[1]);
			break;
		case GLCD_CTL_DATA_READ:
			gpioHigh(varGLCDPortControl, varGLCDPinControl[0] | varGLCDPinControl[1]);
			break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864DataPinSetup
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864DataPinSetup(uint8_t GLCD_DATA_)
{
	switch (GLCD_DATA_)
	{
		case GLCD_DATA_WRITE:
			GPIOPinTypeGPIOOutput(varGLCDPortData, 0xFF);
			break;
		case GLCD_DATA_READ:
			GPIOPinTypeGPIOInput(varGLCDPortData, 0xFF);
			GPIOPadConfigSet(varGLCDPortData, 0xFF, GPIO_STRENGTH_8MA, GPIO_IN_PULL_UP);
			break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864Setup
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864Setup(void)
{
	/* Parallel interface */
	gpioHigh(varGLCDPortControl, varGLCDPinControl[3]);	// PSB = '1'

	/* Function Set */
	glcd12864FunctionSet(true);							// 8-bit interface, basic instruction

	/* Display Control */
	glcd12864DisplayMode(true, false, false);			// Display ON, cursor-blink OFF

	/* Entry Mode Set */
	glcd12864Wait();
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);
	glcd12864DataPinSetup(GLCD_DATA_WRITE);
	GPIOPinWrite(varGLCDPortData, 0xFF, 0x06);			// Cursor move to right, DDRAM AC plus 1
	glcd12864Implement();

	/* Cursor Display Shift */
	glcd12864Wait();
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);
	glcd12864DataPinSetup(GLCD_DATA_WRITE);
	GPIOPinWrite(varGLCDPortData, 0xFF, 0x10);			// No cursor or display shift operation
	glcd12864Implement();

	/* Display Clear */
	glcd12864Clear();									// DDRAM = "20H",  set DDRAM AC = "00H"

	/* Return Home */
	glcd12864Home();									// Set DDRAM AC = "00H", cursor -> origin
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864FunctionSet
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864FunctionSet(bool isBasicInstruction)
{
	glcd12864Wait();									// Wait if busy
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);	// Config as Instruction write
	glcd12864DataPinSetup(GLCD_DATA_WRITE);				// Config as Output
	if(isBasicInstruction) 	GPIOPinWrite(varGLCDPortData, 0xFF, 0x30);
														// 8-bit interface, basic instruction
	else					GPIOPinWrite(varGLCDPortData, 0xFF, 0x34);
														// 8-bit interface, extended instruction
	glcd12864Implement();								// Enable writting
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864Implement
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864Implement(void)
{
	gpioHigh(varGLCDPortControl, varGLCDPinControl[2]);		// Enable
	SysCtlDelay(10);
	gpioLow(varGLCDPortControl, varGLCDPinControl[2]);		// Disable
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864Busy
 *	Purpose	:
 *	Input	:	None
 *	Output	:
 */
uint8_t
glcd12864Busy(void)
{
	/* Instruction Read */
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_READ);
	glcd12864DataPinSetup(GLCD_DATA_READ);

	/* Read */
	gpioHigh(varGLCDPortControl, varGLCDPinControl[2]);				// Enable
	uint8_t varRead = (uint8_t)gpioRead(varGLCDPortData, 0xFF);		// Read
	gpioLow(varGLCDPortControl, varGLCDPinControl[2]);				// Disable

	/* Return */
	return varRead;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864Wait
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864Wait(void)
{
	while(glcd12864Busy() & 0x80);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864Clear
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864Clear(void)
{
	glcd12864Wait();									// Wait if busy
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);	// Config as Instruction write
	glcd12864DataPinSetup(GLCD_DATA_WRITE);				// Config as Output
	GPIOPinWrite(varGLCDPortData, 0xFF, 0x01);			// Write to GLCD
	glcd12864Implement();								// Enable writting
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864Home
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864Home(void)
{
	glcd12864Wait();									// Wait if busy
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);	// Config as Instruction write
	glcd12864DataPinSetup(GLCD_DATA_WRITE);				// Config as Output
	GPIOPinWrite(varGLCDPortData, 0xFF, 0x02);			// Write to GLCD
	glcd12864Implement();								// Enable writting
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864DisplayTurn
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
bool
glcd12864DisplayMode(bool isDisplayTurnOn, bool isCursorOn, bool isBlinkOn)
{
	/* Declare */
	uint8_t varCmd = 0x08;								// Offset of Command

	/* Wait & Config */
	glcd12864Wait();									// Wait if busy
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);	// Config as Instruction write
	glcd12864DataPinSetup(GLCD_DATA_WRITE);				// Config as Output

	/* Set Command */
	if(isDisplayTurnOn)	varCmd |=  0x04;				// Display On/Off
	else				varCmd &= ~0x04;
	if(isCursorOn)		varCmd |=  0x02;				// Cursor On/Off
	else				varCmd &= ~0x02;
	if(isBlinkOn)		varCmd |=  0x01;				// Blink On/Off
	else				varCmd &= ~0x01;

	/* Set Data pins */
	GPIOPinWrite(varGLCDPortData, 0xFF, varCmd);

	/* Implement */
	glcd12864Implement();								// Enable writting

	/* Return */
	return isDisplayTurnOn;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864PrintChar
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864PrintChar(uint8_t varX, uint8_t varY, uint8_t varChar)
{
	/* Guarantee that Y must be in range form 1 to 4 */
	varY %= 4;

	/* Guarantee that X must be in range form 0 to 15 */
	varX %= 16;

	/* Get varX */
	switch (varY)
	{
		case 0: varX += 0X80; break;
		case 1: varX += 0X90; break;
		case 2: varX += 0X88; break;
		case 3: varX += 0X98; break;
	}

	/* Write to GLCD */
	glcd12864WriteCmd(varX);
	glcd12864WriteData(varChar);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864PrintStr
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864PrintStr(uint8_t varX, uint8_t varY, uint8_t str[])
{
	/* Declare */
	uint8_t i = 0, varXAddr;

	/* Guarantee that Y must be in range form 1 to 4 */
	varY %= 4;

	/* Guarantee that X must be in range form 0 to 15 */
	varX %= 16;
	varXAddr = varX;

	/* Get varXAddr */
	switch (varY)
	{
		case 0: varXAddr += 0X80; break;
		case 1: varXAddr += 0X90; break;
		case 2: varXAddr += 0X88; break;
		case 3: varXAddr += 0X98; break;
	}

	/* Write to GLCD */
	glcd12864WriteCmd(varXAddr);
	while(str[i] != '\0')
	{
		if(varX <= 0x0F)
		{
			glcd12864WriteData(str[i]);
			i++;
			varX++;
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864WriteCmd
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864WriteCmd(uint8_t varCmd)
{
	glcd12864Wait();									// Wait if busy
	glcd12864CtlPinSetup(GLCD_CTL_INSTRUCTION_WRITE);	// Config as Instruction write
	glcd12864DataPinSetup(GLCD_DATA_WRITE);				// Config as Output
	GPIOPinWrite(varGLCDPortData, 0xFF, varCmd);		// Set Data pins
	glcd12864Implement();								// Enable writting
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	glcd12864WriteData
 *	Purpose	:
 *	Input	:
 *	Output	:	None
 */
void
glcd12864WriteData(uint8_t varData)
{
	glcd12864Wait();									// Wait if busy
	glcd12864CtlPinSetup(GLCD_CTL_DATA_WRITE);			// Config as Data write
	glcd12864DataPinSetup(GLCD_DATA_WRITE);				// Config as Output
	GPIOPinWrite(varGLCDPortData, 0xFF, varData);		// Set Data pins
	glcd12864Implement();								// Enable writting
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
 *	END OF GLCD_12864.0.101.c
 *************************************************************************************************/
