/*
 *	File			:	USB.1.0.1.h
 *	Date created	:	15/12/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Version			:	1.0.1
 *	Description		:	Header of USB
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef USB_1_0_1_H_
#define USB_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

/* Producer */
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/usb.h"
#include "driverlib/udma.h"

#include "usblib/usblib.h"
#include "usblib/usbhid.h"
#include "usblib/host/usbhost.h"
#include "usblib/host/usbhhid.h"
#include "usblib/host/usbhhidkeyboard.h"

/* My */
#include "LAUNCHPAD.1.0.1.h"
#include "CLK.1.0.1.h"
#include "TIMER.1.0.1.h"
#include "GPIO.1.0.1.h"
#include "UART.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* This enumerated type is used to hold the states of the keyboard */
typedef	enum
{
    STATE_NO_DEVICE,			// No device is present
    STATE_KEYBOARD_INIT,		// Keyboard has been detected and needs to be initialized
    STATE_KEYBOARD_CONNECTED,	// Keyboard is connected and waiting for events
    STATE_KEYBOARD_UPDATE,		// Keyboard has received a key press that requires updating
    STATE_UNKNOWN_DEVICE,		// An unsupported device has been attached
    STATE_POWER_FAULT			// A power fault has occurred
} usb_State;
extern	usb_State	varUsbState;
//-------------------------------------------------------------------------------------------------
/* Setup */
uint32_t
usbSetup			(void);
//-------------------------------------------------------------------------------------------------
/* Update */
void
usbUpdate			(void);
//-------------------------------------------------------------------------------------------------
/* String */
void
usbStr				(uint8_t ui8Char);
//-------------------------------------------------------------------------------------------------
/* Handler */
void
TIMER_USB_ISR		(void);
void
USBHCDEvents		(void *pvData);
void
KeyboardCallback	(tUSBHKeyboard *psKbInstance, uint32_t ui32Event, uint32_t ui32MsgParam,
																				void *pvMsgData);

/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Get Tick */
static	uint32_t
usbGetTickMs		(void);
static	void
usbBackspace		(void);


#endif /* USB_1_0_1_H_ */

