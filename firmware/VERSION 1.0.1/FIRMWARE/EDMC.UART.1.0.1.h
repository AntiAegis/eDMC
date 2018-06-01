/*
 *	File		:	EDMC.UART.1.0.1.h
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of this UART
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	EDMC_UART_1_0_1_H_
#define	EDMC_UART_1_0_1_H_


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
#include "CLK.1.0.1.h"
#include "GPIO.1.0.1.h"
#include "UART.1.0.1.h"

/* This project */
#include "EDMC.INDICATOR.1.0.1.h"
#include "EDMC.LED.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Setup */
uint32_t
edmcUartEnable		(void);
uint32_t
edmcUartDisable		(void);
uint32_t
edmcUartConfig		(char strType[], char str[]);
//-------------------------------------------------------------------------------------------------
/* Status */
void
edmcUartStatus		(void);
//-------------------------------------------------------------------------------------------------
/* Buffer */
bool
edmcUartBuffPrint	(uint8_t ui8Start, uint8_t ui8Num, char strFormat);
//-------------------------------------------------------------------------------------------------
/* Send */
void
edmcUartSend		(char str[], uint32_t ui32Time, uint32_t ui32Delay);
//-------------------------------------------------------------------------------------------------
/* Interrupt */
void
EDMC_UART_ISR		(void);


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Config */
static	bool
lenEncode			(char str[], uint8_t* pui8Len);
static	bool
stopEncode			(char str[], uint8_t* pui8Stop);
static	bool
parEncode			(char str[], uint8_t* pui8Par);

static	bool
lenDecode			(uint8_t ui8Len, char str[]);
static	bool
stopDecode			(uint8_t ui8Stop, char str[]);
static	bool
parDecode			(uint8_t ui8Par, char str[]);


#endif	/* EDMC_UART_1_0_1_H_ */

