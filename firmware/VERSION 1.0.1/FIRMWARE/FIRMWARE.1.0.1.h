/*
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Header of Firmware
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef	EDMC_FIRMWARE_1_0_1_H_
#define	EDMC_FIRMWARE_1_0_1_H_


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

/* This project */
#include "FIRMWARE/EDMC.OS.1.0.1.h"
#include "FIRMWARE/EDMC.LED.1.0.1.h"
#include "FIRMWARE/EDMC.INDICATOR.1.0.1.h"
#include "FIRMWARE/EDMC.KEYPAD.1.0.1.h"
#include "FIRMWARE/EDMC.LCD.1.0.1.h"
#include "FIRMWARE/EDMC.KEYBOARD.1.0.1.h"
#include "FIRMWARE/EDMC.SDCARD.1.0.1.h"
#include "FIRMWARE/EDMC.ICDI.1.0.1.h"
#include "FIRMWARE/EDMC.UART.1.0.1.h"
#include "FIRMWARE/EDMC.SPI.1.0.1.h"
#include "FIRMWARE/EDMC.I2C.1.0.1.h"
#include "FIRMWARE/EDMC.WIFI.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Operating system ******************************************************************************/
/* Declare */
#define	fwThrdDef					osThreadDef				// Declare of Thread task
#define	fwThrdID					osThreadId				// Declare of Thread ID
#define	fwMessDef					osMessageQDef			// Declare of Message task
#define	fwMessID					osMessageQId			// Declare of Message ID
#define	fwEvent						osEvent					// Declare of Event
// With Software interrupt, user must register in "EDMC.OS.1.0.1.h"

/* Priority */
#define fwPriorIdle					osPrior(Idle)			// Priority: idle (lowest)
#define fwPriorLow					osPrior(Low)			// Priority: low
#define fwPriorBelowNormal			osPrior(BelowNormal)	// Priority: below normal
#define fwPriorNormal				osPrior(Normal)			// Priority: normal (default)
#define fwPriorAboveNormal			osPrior(AboveNormal)	// Priority: above normal
#define fwPriorHigh					osPrior(High)			// Priority: high
#define fwPriorRealtime				osPrior(Realtime)		// Priority: realtime (highest)
#define	fwPrior(x)					(fwPrior##x)			// Get priority name

/* Function */
#define	fwThrdEnable(thrdFnc)		osThreadCreate(osThread(fnc),NULL)
#define	fwThrdDisable(thrdID)		osThreadTerminate(thrdID)
#define	fwThrdNext					osThreadYield()

#define	fwSwiSet(thrdID,i32Sig)		osSignalSet(thrdID,i32Sig)
#define	fwSwiWait(i32Sig)			osSignalWait(i32Sig,osWaitForever)
#define	fwSwiClr(thrdID,i32Sig) 	osSignalClear(thrdID,i32Sig)

#define	fwDelay(ui32Ms)				osDelay(ui32Ms)

#define	fwMessSend(messID,ui32Src)	osMessagePut(messID,ui32Src,0)
#define	fwMessGet(messID)			osMessageGet(messID,0)
#define	fwEventValue(event)			(event.value.v)

/* LED *******************************************************************************************/
/* Get LED name */
#define	fwLed(x)					LED(x)

/* Function */
#define	fwLedState					edmcLedState

/* Indicator *************************************************************************************/
#define	fwIdc						edmcIdcNotify
#define	fwIdcBin					edmcIdcBin

/* Keypad ****************************************************************************************/
/* Get Button name */
#define	fwBtn(x)					BTN(x)

/* Function */
#define	fwBtnGet					kpReadBtnFromISR()

/* LCD *******************************************************************************************/
#define	fwLcdEnable					edmcLcdEnable()
#define	fwLcdDisable				edmcLcdDisable()

/* Keyboard **************************************************************************************/
#define	fwKbEnable					edmcKbEnable()
#define	fwKbDisable					edmcKbDisable()

/* SD Card ***************************************************************************************/
#define	fwSdcEnable					edmcSdcEnable()
#define	fwSdcDisable				edmcSdcDisable()

/* ICDI ******************************************************************************************/
#define	fwIcdiEnable				edmcIcdiEnable()
#define	fwIcdiDisable				edmcIcdiDisable()
#define	fwIcdiSysInfo				edmcIcdiSendSysInfo()

/* UART ******************************************************************************************/
#define	fwUartEnable				edmcUartEnable()
#define	fwUartDisable				edmcUartDisable()
#define	fwUartSend					edmcUartSend

/* SPI *******************************************************************************************/
#define	fwSpiEnable					edmcSpiEnable()
#define	fwSpiDisable				edmcSpiDisable()

/* I2C *******************************************************************************************/
#define	fwI2cEnable					edmcI2cEnable()
#define	fwI2cDisable				edmcI2cDisable()

/* Wifi ******************************************************************************************/
#define	fwWifiEnable				edmcWifiEnable()
#define	fwWifiDisable				edmcWifiDisable()


#endif	/* EDMC_FIRMWARE_1_0_1_H_ */

