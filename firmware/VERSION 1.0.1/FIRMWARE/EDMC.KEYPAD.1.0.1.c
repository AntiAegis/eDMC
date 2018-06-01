/*
 *	File		:	EDMC.KEYPAD.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of Keypad
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.KEYPAD.1.0.1.h"
#include "EDMC.OS.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	KP_PORT			GPIO_PORT_K
#define	KP_PIN_IN_3		GPIO_PIN_7
#define	KP_PIN_IN_2		GPIO_PIN_6
#define	KP_PIN_IN_1		GPIO_PIN_5
#define	KP_PIN_IN_0		GPIO_PIN_4
#define	KP_PIN_OUT_3	GPIO_PIN_3
#define	KP_PIN_OUT_2	GPIO_PIN_2
#define	KP_PIN_OUT_1	GPIO_PIN_1
#define	KP_PIN_OUT_0	GPIO_PIN_0
#define	KP_PIN_IN		(KP_PIN_IN_3 | KP_PIN_IN_2 | KP_PIN_IN_1 | KP_PIN_IN_0)
#define	KP_PIN_OUT		(KP_PIN_OUT_3 | KP_PIN_OUT_2 | KP_PIN_OUT_1 | KP_PIN_OUT_0)
#define	KP_PIN			(KP_PIN_IN | KP_PIN_OUT)

//-------------------------------------------------------------------------------------------------
/* Password */
static	bool			st_isPassEnable = true;			// Enable/Disable password of Keypad
static	bool			st_isPassRight  = true;			// Indicate whether password is passed

#define	KP_PASS			"200997"						// String of password
#define	KP_BUFF_LENGTH	6								// Length of assword characters
static	uint8_t			st_pui8PassBuff[KP_BUFF_LENGTH];// Store password characters
static	uint8_t			st_ui8PassPos = 255;			// Position of current character in buffer

//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	ui8Btn: Read button
 *	Output		:	None
 *	Description	:	Get password character
 */
static	void	kpPassData(tKpBtn ui8Btn)
{
	/* Get data */
	if		(ui8Btn)								st_pui8PassBuff[st_ui8PassPos] = ui8Btn + 47;
	
	/* Indicate */
	if		(st_ui8PassPos == 0)					edmcIdcNotify("Keypad: *");
	else if	(st_ui8PassPos == KP_BUFF_LENGTH - 1)	edmcIdcNotify("*\n");
	else											edmcIdcNotify("*");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Clear password
 */
static	void	kpPassClr(void)
{
	/* Declare */
	uint8_t i;
	
	/* Reset value of buffer */
	for(i = 0; i < KP_BUFF_LENGTH; i++)	st_pui8PassBuff[i] = 0;
	
	/* Reset value of counter */
	st_ui8PassPos = 255;
	
	/* New line */
	edmcIdcNotify("\nKeypad: Clear\n");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Right/Wrong password
 *	Description	:	Confirm password
 */
static	bool	kpPassCfm(void)
{
	/* Declare */
	uint8_t i;
	
	/* Check position */
	if(st_ui8PassPos < KP_BUFF_LENGTH - 1)	return false;
	
	/* Check content of password */
	for(i = 0; i < KP_BUFF_LENGTH; i++)	if(st_pui8PassBuff[i] != KP_PASS[i])	return false;
	
	/* Return */
	return true;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Do these things if password is right
 */
static	void	kpPassRight(void)
{
	/* Set bit st_isPassRight */
	st_isPassRight = true;
	
	/* Notify */
	edmcIdcNotify("\nKeypad: Correct password\n");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Do these things if password is wrong
 */
static	void	kpPassWrong(void)
{
	/* Clear bit st_isPassRight */
	st_isPassRight = false;
	
	/* Notify */
	edmcIdcNotify("\nKeypad: <Error> Wrong password\n");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Do these things if password is overflow
 */
static	void	kpPassOvf(void)
{
	/* Notify */
	edmcIdcNotify("\nKeypad: <Error> Overflow\n");
}
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
 *	Output		:	Status of Setup
 *	Description	:	Setup Keypad
 */
uint32_t	edmcKpEnable(void)
{
	/* Input */
	gpioInputSetup(KP_PORT, KP_PIN_IN, GPIO_IN_PULL_UP);

	/* Output */
	gpioOutputSetup(KP_PORT, KP_PIN_OUT);

	/* Interrupt */
	gpioIntSetup(KP_PORT, KP_PIN_IN, GPIO_IN_DETECT_FALL, EDMC_KP_ISR);

	/* Notify */
	edmcIdcNotify("Keypad: Enabled\n");

	/* LED */
	edmcLedState(LED(KP), 1);

	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Right or Wrong
 *	Description	:	Check whether Password is passed or not
 */
bool	edmcKpPassIsRight(void)
{
	return	st_isPassRight;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Lock Password in Keypad
 */
void	edmcKpPassDisable(void)
{
	st_isPassRight 	= false;
	st_isPassEnable = false;
	edmcIdcNotify("Keypad: Password is disabled\n");
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Sweep keypad
 */
void	edmcKpSweep(void)
{
	/* Declare */
	static	uint8_t	i = 255;
	
	/* Update state */
	i++;
	if(i == 4)	i = 0;
	
	/* Sweep */
	switch(i)
	{
		case 0:
			gpioHigh(KP_PORT, KP_PIN_OUT_3);
			gpioLow(KP_PORT, KP_PIN_OUT_0);
			break;
		case 1:
			gpioHigh(KP_PORT, KP_PIN_OUT_0);
			gpioLow(KP_PORT, KP_PIN_OUT_1);
			break;
		case 2:
			gpioHigh(KP_PORT, KP_PIN_OUT_1);
			gpioLow(KP_PORT, KP_PIN_OUT_2);
			break;
		case 3:
			gpioHigh(KP_PORT, KP_PIN_OUT_2);
			gpioLow(KP_PORT, KP_PIN_OUT_3);
			break;
	}
}//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Pressed button
 *	Description	:	Read which button is pressed
 */
#define	IN(x)		KP_PIN_IN_##x	// Get name of Input pin
#define	OUT(x)		KP_PIN_OUT_##x	// Get name of Output pin

tKpBtn	kpReadBtnFromISR(void)
{
	/* Read */
	uint8_t ui8Btn = gpioRead(KP_PORT, KP_PIN);
	ui8Btn = (~ui8Btn & KP_PIN_IN) | (~ui8Btn & KP_PIN_OUT);
	
	/* Process */
	switch(ui8Btn & KP_PIN_IN)
	{
	case IN(3):
		switch(ui8Btn & KP_PIN_OUT)
		{
			case OUT(3)	:	return BTN(1);
			case OUT(2)	:	return BTN(2);
			case OUT(1)	:	return BTN(3);
			case OUT(0)	:	return BTN(A);
			default		:	return BTN(None);
		}
	case IN(2):
		switch(ui8Btn & KP_PIN_OUT)
		{
			case OUT(3)	:	return BTN(4);
			case OUT(2)	:	return BTN(5);
			case OUT(1)	:	return BTN(6);
			case OUT(0)	:	return BTN(B);
			default		:	return BTN(None);
		}
	case IN(1):
		switch(ui8Btn & KP_PIN_OUT)
		{
			case OUT(3)	:	return BTN(7);
			case OUT(2)	:	return BTN(8);
			case OUT(1)	:	return BTN(9);
			case OUT(0)	:	return BTN(C);
			default		:	return BTN(None);
		}
	case IN(0):
		switch(ui8Btn & KP_PIN_OUT)
		{
			case OUT(3)	:	return BTN(Clr);
			case OUT(2)	:	return BTN(0);
			case OUT(1)	:	return BTN(Cfm);
			case OUT(0)	:	return BTN(D);
			default		:	return BTN(None);
		}
	default				:	return BTN(None);
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Process password
 */
void	edmcKpPassPrc(tKpBtn ui8Btn)
{
	/* Declare */
	static tKpBtn 	ui8BtnLast = edmcKpBtn_None;
	static uint8_t	count = 0;

	/* Check whether button is valid */
	if((ui8Btn) && (ui8Btn == ui8BtnLast))	count++;	// Increase count if holding button
	else									count = 0;	// Reset count if not holding button
	ui8BtnLast = ui8Btn;								// Update read button
	if(count < 5)	return;								// Escape if holding time is not enough
	else			count = 0;							// Rst count and ctn if enough holding time

	/* Update position */
	st_ui8PassPos++;

	/* If "Cfm" */
	if(ui8Btn == edmcKpBtn_Cfm)
	{
		if(kpPassCfm())	kpPassRight();
		else			kpPassWrong();
	}

	/* If not "Cfm" */
	else
	{
		/* If overflow digit */
		if(st_ui8PassPos >= KP_BUFF_LENGTH)
		{
			if(ui8Btn == edmcKpBtn_Clr)	kpPassClr();		// If "Clr", reset
			else						kpPassOvf();		// Else, notify "Overflow"
		}
		
		/* If not overflow */
		else
		{
			if(ui8Btn == edmcKpBtn_Clr)	kpPassClr();		// If "Clr", reset
			else						kpPassData(ui8Btn);	// Else
		}
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Interrupt of Keypad (GPIO portK)
 */
void	EDMC_KP_ISR(void)
{
	/* Read button */
	tKpBtn	ui8Btn = kpReadBtnFromISR();
	
	/* Password */
	if(st_isPassEnable)
	{
		osMessagePut(osMessIdKpPassPrc, (uint32_t)ui8Btn, 0);
		osSignalSet(osIDKpPassPrc, SWI_KP_PASS_PRC);
	}
	
	/* Exit ISR */
	gpioIntExit(KP_PORT, KP_PIN);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */

