/*
 *	File			:	GLCD_12864.0.0.101.h
 *	Date created	:	30/11/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	0.0.101
 *	Description		:	Library of LCD Graphic 128x64
 */
/**************************************************************************************************
 *							PROCESS OF HANDLING WITH GLCD
 *		* Step 1	: 	Config as Instruction Read (Control pins) and Input (Data pins)
 *		* Step 2	: 	Read Busy Flag. If BF = '1', wait until BF = '0'
 *		* Step 3	:	Config as Instrucion Write (Control pins) and Output (Data pins)
 *		* Step 4	:	Set Data pins
 *		* Step 5	:	Enable, delay 10 machine cycles, and Disable
 *************************************************************************************************/
/**************************************************************************************************
 *	PRE-DEIFINITIONs
 *************************************************************************************************/
#ifndef GLCD_12864_0_0_101_H_
#define GLCD_12864_0_0_101_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Producing Library */
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

/* My Library */
#include "LAUNCHPAD.0.0.101.h"
#include "GPIO.0.0.101.h"

/* This project */


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Hardware */
//#define	GLCD_PIN_VSS					1	// Ground
//#define	GLCD_PIN_VDD					2	// VCC
//#define	GLCD_PIN_V0						3	// Contrast
//#define	GLCD_PIN_RS						4	// Control/Data register (parallel), Disable/Enable chip (serial)
//#define	GLCD_PIN_RW						5	// Write/Read (parallel), Data input (Serial)
//#define	GLCD_PIN_E						6	// Disable/Enable (parallel), Clock (Serial)
//#define	GLCD_PIN_DB0					7	// Data 0
//#define	GLCD_PIN_DB1					8	// Data 1
//#define	GLCD_PIN_DB2					9	// Data 2
//#define	GLCD_PIN_DB3					10	// Data 3
//#define	GLCD_PIN_DB4					11	// Data 4
//#define	GLCD_PIN_DB5					12	// Data 5
//#define	GLCD_PIN_DB6					13	// Data 6
//#define	GLCD_PIN_DB7					14	// Data 7
//#define	GLCD_PIN_PSB					15	// Serial/Parallel
//#define	GLCD_PIN_NC						16	// No connection
//#define	GLCD_PIN_RST					17	// Reset/Normal
//#define	GLCD_PIN_VOUT					18	// Used with GLCD_PIN_V0 to control contrast
//#define	GLCD_PIN_A						19	// Anode LED
//#define	GLCD_PIN_K						20	// Cathod LED

//-------------------------------------------------------------------------------------------------
/* Setup */
#define	GLCD_CTL_INSTRUCTION_WRITE			0
#define	GLCD_CTL_INSTRUCTION_READ			1
#define	GLCD_CTL_DATA_WRITE					2
#define	GLCD_CTL_DATA_READ					3

#define	GLCD_DATA_WRITE						0
#define	GLCD_DATA_READ						1


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void
glcd12864PinSetup		(uint32_t PortControl, uint32_t PinRS, uint32_t PinRW, uint32_t PinE,
															uint32_t PinPSB, uint32_t PortData);
void
glcd12864CtlPinSetup	(uint8_t GLCD_CTL_);
void
glcd12864DataPinSetup	(uint8_t GLCD_DATA_);
void
glcd12864Setup			(void);

/* Control */
void
glcd12864FunctionSet	(bool isBasicInstruction);
void
glcd12864Implement		(void);
uint8_t
glcd12864Busy			(void);
void
glcd12864Wait			(void);

/* Display */
void
glcd12864Clear			(void);
void
glcd12864Home			(void);
bool
glcd12864DisplayMode	(bool isDisplayTurnOn, bool isCursorOn, bool isBlinkOn);
void
glcd12864PrintChar		(uint8_t varX, uint8_t varY, uint8_t varChar);
void
glcd12864PrintStr		(uint8_t varX, uint8_t varY, uint8_t str[]);

/* Instruction & Data */
void
glcd12864WriteCmd		(uint8_t varCmd);
uint8_t
glcd12864ReadCmd		(void);
void
glcd12864WriteData		(uint8_t varData);
uint8_t
glcd12864ReadData		(void);


/**************************************************************************************************
 *	END OF GLCD_12864.0.0.101.h
 *************************************************************************************************/
#endif /* GLCD_12864_0_0_101_H_ */
