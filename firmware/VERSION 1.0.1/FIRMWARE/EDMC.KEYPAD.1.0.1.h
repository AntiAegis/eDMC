/*
 *	File		:	EDMC.KEYPAD.1.0.1.h
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of this Keypad
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	EDMC_KEYPAD_1_0_1_H_
#define	EDMC_KEYPAD_1_0_1_H_


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
#include "EDMC.LED.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Enum of Button */
typedef enum
{
	edmcKpBtn_None	= 0,
	edmcKpBtn_0		= 1,
	edmcKpBtn_1		= 2,
	edmcKpBtn_2		= 3,
	edmcKpBtn_3		= 4,
	edmcKpBtn_4		= 5,
	edmcKpBtn_5		= 6,
	edmcKpBtn_6		= 7,
	edmcKpBtn_7		= 8,
	edmcKpBtn_8		= 9,
	edmcKpBtn_9		= 10,
	edmcKpBtn_A		= 11,
	edmcKpBtn_B		= 12,
	edmcKpBtn_C		= 13,
	edmcKpBtn_D		= 14,
	edmcKpBtn_Clr	= 15,
	edmcKpBtn_Cfm	= 16
} tKpBtn;

#define	BTN(x)		(edmcKpBtn_##x)	// Get name of Button
//-------------------------------------------------------------------------------------------------
/* Setup */
uint32_t
edmcKpEnable		(void);
//-------------------------------------------------------------------------------------------------
/* Sweep */
void
edmcKpSweep			(void);
//-------------------------------------------------------------------------------------------------
/* Read button */
tKpBtn
kpReadBtnFromISR	(void);
//-------------------------------------------------------------------------------------------------
/* Password */
bool
edmcKpPassIsRight	(void);
void
edmcKpPassDisable	(void);
void
edmcKpPassPrc		(tKpBtn ui8Btn);
//-------------------------------------------------------------------------------------------------
/* Interrupt */
void
EDMC_KP_ISR			(void);


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Password */
static	void
kpPassData			(tKpBtn ui8Btn);
static	void
kpPassClr			(void);
static	bool
kpPassCfm			(void);
static	void
kpPassRight			(void);
static	void
kpPassWrong			(void);
static	void
kpPassOvf			(void);


#endif	/* EDMC_KEYPAD_1_0_1_H_ */
