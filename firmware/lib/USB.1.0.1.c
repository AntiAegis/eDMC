/*
 *	File			:	USB.1.0.1.c
 *	Date created	:	15/12/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	version			:	1.0.1
 *	Description		:	Source file for USB
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
//#define	USE_SW_CMD_LINE


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "USB.1.0.1.h"

#ifdef	USE_SW_CMD_LINE
#include "FIRMWARE/EDMC.OS.1.0.1.h"
#include "SOFTWARE/Command Line/SW.CMD.1.0.1.h"
#endif	/* USE_SW_CMD_LINE */


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* DMA */
#if defined(ewarm)
#pragma data_alignment=1024
tDMAControlTable			g_sDMAControlTable[6];
#elif defined(ccs)
#pragma DATA_ALIGN(g_sDMAControlTable, 1024)
tDMAControlTable			g_sDMAControlTable[6];
#else
tDMAControlTable			g_sDMAControlTable[6] __attribute__ ((aligned(1024)));
#endif
//-------------------------------------------------------------------------------------------------
/* The number of SysTick ticks per second */
#define TICKS_PER_SECOND 	100
#define MS_PER_SYSTICK 		(1000 / TICKS_PER_SECOND)
//-------------------------------------------------------------------------------------------------
/* Time elapsed since last call to GetTickms() */
static 	uint32_t			g_ui32SysTickCount;
static 	uint32_t			g_ui32LastTick;
//-------------------------------------------------------------------------------------------------
/* The size of the host controller's memory pool in bytes */
#define HCD_MEMORY_SIZE		128
//-------------------------------------------------------------------------------------------------
/* The memory pool to provide to the Host controller driver */
static 	uint8_t				g_pHCDPool[HCD_MEMORY_SIZE];
//-------------------------------------------------------------------------------------------------
/* The size of the keyboard device interface's memory pool in bytes */
#define KEYBOARD_MEM_SIZE	128
//-------------------------------------------------------------------------------------------------
/* The memory pool to provide to the keyboard device */
static 	uint8_t				g_pui8Buffer[KEYBOARD_MEM_SIZE];
static 	uint8_t				varCountBuff = 255;
//-------------------------------------------------------------------------------------------------
/* Declare the USB Events driver interface */
static 	const 	tUSBHostClassDriver		g_sUSBEventDriver =
{
	USB_CLASS_EVENTS,
	0,
	0,
	USBHCDEvents
};
//-------------------------------------------------------------------------------------------------
/* Keyboard class drivers */
static tUSBHostClassDriver const * const g_ppHostClassDrivers[] =
{
    &g_sUSBHIDClassDriver,
    &g_sUSBEventDriver
};
//-------------------------------------------------------------------------------------------------
/* This global holds the number of class drivers in the g_ppHostClassDrivers list */
static const uint32_t g_ui32NumHostClassDrivers =
									sizeof(g_ppHostClassDrivers) / sizeof(tUSBHostClassDriver *);
//-------------------------------------------------------------------------------------------------
/* The instance data for the MSC driver */
static 	tUSBHKeyboard *g_psKeyboardInstance = 0;
//-------------------------------------------------------------------------------------------------
/* This variable holds the current status of the modifiers keys */
static 	uint32_t g_ui32Modifiers = 0;
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Number of ticks
 *	Description	:	Number of ticks since the last time this function was called
 */
static	uint32_t	usbGetTickMs(void)
{
	uint32_t ui32RetVal;
	uint32_t ui32Saved;

	ui32RetVal = g_ui32SysTickCount;
	ui32Saved = ui32RetVal;

	if(ui32Saved > g_ui32LastTick) ui32RetVal = ui32Saved - g_ui32LastTick;
	else ui32RetVal = g_ui32LastTick - ui32Saved;

	/* This could miss a few milliseconds but the timings here are on a much larger scale */
	g_ui32LastTick = ui32Saved;

	/* Return the number of milliseconds since the last time this was called */
	return(ui32RetVal * MS_PER_SYSTICK);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static	void	usbBackspace(void)
{
	uartSendStr(UART_ICDI, "\b \b");
}


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* This enumerated type is used to hold the states of the keyboard */
usb_State		varUsbState;
//-------------------------------------------------------------------------------------------------
/* Keyboard map */
extern const tHIDKeyboardUsageTable		g_sUSKeyboardMap;
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	Status of Setup
 *	Description	:	Setup USB
 */
uint32_t	usbSetup(void)
{
	/* Declare */
	uint32_t ui32PLLRate;

	/* Initially wait for device connection */
	varUsbState = STATE_NO_DEVICE;

	/* Config GPIO */
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOQ);
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0xff;
	ROM_GPIOPinConfigure(GPIO_PD6_USB0EPEN);
	ROM_GPIOPinTypeUSBAnalog(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	ROM_GPIOPinTypeUSBDigital(GPIO_PORTD_BASE, GPIO_PIN_6);
	ROM_GPIOPinTypeUSBAnalog(GPIO_PORTL_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	ROM_GPIOPinTypeGPIOInput(GPIO_PORTQ_BASE, GPIO_PIN_4);

	/* Create 100Hz timer interrupt */
	timerSetup(TIMER0, TIMER_A, TIMER_CFG_PERIODIC_UP, true, 1, ui32ClkFreq / TICKS_PER_SECOND);

	/* Enable the uDMA controller and set up the control table base */
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	ROM_uDMAEnable();
	ROM_uDMAControlBaseSet(g_sDMAControlTable);

	/* Initialize the USB stack in host mode. No callback is needed at this time */
	USBStackModeSet(0, eUSBModeHost, 0);

	/* Register the host class drivers */
	USBHCDRegisterDrivers(0, g_ppHostClassDrivers, g_ui32NumHostClassDrivers);

	/* Open an instance of the keyboard driver */
	g_psKeyboardInstance = USBHKeyboardOpen(KeyboardCallback, g_pui8Buffer, KEYBOARD_MEM_SIZE);

	/* Initialize the power configuration */
	USBHCDPowerConfigInit(0, USBHCD_VBUS_AUTO_HIGH | USBHCD_VBUS_FILTER);

	/* Tell the USB library the CPU clock and the PLL frequency */
	SysCtlVCOGet(SYSCTL_XTAL_25MHZ, &ui32PLLRate);
	USBHCDFeatureSet(0, USBLIB_FEATURE_CPUCLK, &ui32ClkFreq);
	USBHCDFeatureSet(0, USBLIB_FEATURE_USBPLL, &ui32PLLRate);

	/* Initialize the USB controller for host operation */
	USBHCDInit(0, g_pHCDPool, HCD_MEMORY_SIZE);
		
	/* Return */
	return 0;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	None
 *	Output		:	None
 *	Description	:	Update USB state
 */
void	usbUpdate(void)
{
	/* Tell the OTG library code how much time has passed in milliseconds since the last call */
	USBOTGMain(usbGetTickMs());

	switch(varUsbState)
	{
		/* This state is entered when they keyboard is first detected */
		case STATE_KEYBOARD_INIT:
		{
			/* Initialized the newly connected keyboard */
			USBHKeyboardInit(g_psKeyboardInstance);

			/* Proceed to the keyboard connected state */
			varUsbState = STATE_KEYBOARD_CONNECTED;

			USBHKeyboardModifierSet(g_psKeyboardInstance, g_ui32Modifiers);
			break;
		}
		
		/* If a change that required an update to be sent to the keyboard to change the modifier
			 state then call it and return to the connected state */
		case STATE_KEYBOARD_UPDATE:
		{
			varUsbState = STATE_KEYBOARD_CONNECTED;
			USBHKeyboardModifierSet(g_psKeyboardInstance, g_ui32Modifiers);
			break;
		}
		default:	break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	usbStr(uint8_t ui8Char)
{
	/* Static */
	static	bool	isFrstChar = true;

	/* A zero value indicates there was no textual mapping of this usage code */
	if(ui8Char != 0)
	{
		if(isFrstChar)
		{
			uartSendStr(UART_ICDI, ">>Keyboard: ");
			uartSendChar(UART_ICDI, ui8Char);
			isFrstChar = false;
		}
		else	uartSendChar(UART_ICDI, ui8Char);
	}

	/* Processing if match '\n' */
	if(ui8Char == '\n')
	{
		g_pui8Buffer[varCountBuff] = 0;		// Convert to Null character in string
#ifdef	USE_SW_CMD_LINE
		swCmdStrPrc((char*)g_pui8Buffer);	// Process string with fnc from software "Command Line"
#endif	/* USE_SW_CMD_LINE */
		isFrstChar = true;					// Set flag isFrstChar
		varCountBuff = 255;					// Reset counter
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	TIMER_USB_ISR(void)
{
	/* Update our tick counter */
	g_ui32SysTickCount++;
	
	/* Exit */
	TimerIntClear(TIMER0, TIMER_TIMA_TIMEOUT);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	pvData: Pointer to a tEventInfo structure
 *	Output		:	None
 *	Description	:	Inform when a USB event has occurred that is outside those related to the keyboard
 *					device. This is used to detect unsupported devices being inserted and removed. It
 *					is also used to inform when a power fault has occurred. This function is required
 *					when the g_USBGenericEventDriver is included in the host controller driver array
 *					that is passed in to the USBHCDRegisterDrivers() function
 */
void	USBHCDEvents(void *pvData)
{
	tEventInfo *pEventInfo;

	/* Cast this pointer to its actual type */
	pEventInfo = (tEventInfo*)pvData;

	switch(pEventInfo->ui32Event)
	{
		/* New keyboard detected */
		case USB_EVENT_CONNECTED:
		{
			/* See if this is a HID Keyboard */
			if((USBHCDDevClass(pEventInfo->ui32Instance, 0) == USB_CLASS_HID) &&
			   (USBHCDDevProtocol(pEventInfo->ui32Instance, 0) == USB_HID_PROTOCOL_KEYB))
			{
				uartSendStr(UART_ICDI, "USB0: Keyboard Connected\n");
				varUsbState = STATE_KEYBOARD_INIT;
			}
			break;
		}
		/* Unsupported device detected */
		case USB_EVENT_UNKNOWN_CONNECTED:
		{
			uartSendStr(UART_ICDI, "USB0: Unsupported Device Class Connected\n");
			varUsbState = STATE_UNKNOWN_DEVICE;
			break;
		}
		/* Device has been unplugged */
		case USB_EVENT_DISCONNECTED:
		{
			uartSendStr(UART_ICDI, "USB0: Device Disconnected\n");
			varUsbState = STATE_NO_DEVICE;
			break;
		}
		/* Power Fault has occurred */
		case USB_EVENT_POWER_FAULT:
		{
			uartSendStr(UART_ICDI, "USB0: Power Fault\n");
			varUsbState = STATE_POWER_FAULT;
			break;
		}
		default:	break;
	}
}

//-------------------------------------------------------------------------------------------------
/*
 *	Input		:	pvCBData	: Inorged
 *					ui32Event	: One of the valid events for a keyboard device
 *					ui32MsgParam: Defined by the event that occurs
 *					pvMsgData	: Pointer to data that is defined by the event that occurs
 *	Output		:	None
 *	Description	:	Inform when a keyboard has been plugged in or removed and any time a key is
 *					pressed or released
 */
void
KeyboardCallback(tUSBHKeyboard *psKbInstance, uint32_t ui32Event, uint32_t ui32MsgParam, void *pvMsgData)
{
	/* Declare */
	uint8_t ucChar;

	switch(ui32Event)
	{
		/* New Key press detected */
		case USBH_EVENT_HID_KB_PRESS:
		{
			/* If this was a Caps Lock key then update the Caps Lock state */
			if(ui32MsgParam == HID_KEYB_USAGE_CAPSLOCK)
			{
				varUsbState = STATE_KEYBOARD_UPDATE;
				g_ui32Modifiers ^= HID_KEYB_CAPS_LOCK;
			}
			else if(ui32MsgParam == HID_KEYB_USAGE_SCROLLOCK)
			{
				varUsbState = STATE_KEYBOARD_UPDATE;
				g_ui32Modifiers ^= HID_KEYB_SCROLL_LOCK;
			}
			else if(ui32MsgParam == HID_KEYB_USAGE_NUMLOCK)
			{
				varUsbState = STATE_KEYBOARD_UPDATE;
				g_ui32Modifiers ^= HID_KEYB_NUM_LOCK;
			}
			else if(ui32MsgParam == HID_KEYB_USAGE_BACKSPACE)
			{
				if(varCountBuff != 255) varCountBuff--;
				usbBackspace();
			}
			else
			{
				/* Print the current key out the UART */
				ucChar = (uint8_t)USBHKeyboardUsageToChar(g_psKeyboardInstance, &g_sUSKeyboardMap,
																			(uint8_t)ui32MsgParam);
				/* Save to Buffer */
				if(varCountBuff == KEYBOARD_MEM_SIZE)	varCountBuff = 255;
				g_pui8Buffer[++varCountBuff] = ucChar;

				/* Process and print */
#ifndef	USE_SW_CMD_LINE
				usbStr(ucChar);
#else
				osMessagePut(osMessIdCmdLine, (uint32_t)ucChar, 0);
				osSignalSet(osIdCmdLine, SWI_CMD_LINE);
#endif	/* USE_SW_CMD_LINE */
			}
			break;
		}

		/* This application ignores the state of the shift or control and other special keys */
		case USBH_EVENT_HID_KB_MOD:		break;

		/* This applications ignores the release of keys as well */
		case USBH_EVENT_HID_KB_REL:		break;
	}
}

