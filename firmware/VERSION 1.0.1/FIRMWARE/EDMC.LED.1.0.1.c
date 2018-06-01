/*
 *	File		:	EDMC.LED.1.0.1.c
 *	Date		:	2017/01/10
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of LED
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "EDMC.LED.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Hardware mapping */
#define	LED_PORT_KP			GPIO_PORT_J	// Port J
#define	LED_PIN_KP			GPIO_PIN_1	// PJ1
#define	LED_PORT_LCD		GPIO_PORT_J	// Port J
#define	LED_PIN_LCD			GPIO_PIN_0	// PJ0
#define	LED_PORT_KB			GPIO_PORT_C	// Port C
#define	LED_PIN_KB			GPIO_PIN_4	// PC4
#define	LED_PORT_SDC		GPIO_PORT_C	// Port C
#define	LED_PIN_SDC			GPIO_PIN_5	// PC5
#define	LED_PORT_ICDI		GPIO_PORT_C	// Port C
#define	LED_PIN_ICDI		GPIO_PIN_6	// PC6
#define	LED_PORT_UART		GPIO_PORT_C	// Port C
#define	LED_PIN_UART		GPIO_PIN_7	// PC7
#define	LED_PORT_SPI		GPIO_PORT_F	// Port F
#define	LED_PIN_SPI			GPIO_PIN_1	// PF1
#define	LED_PORT_I2C		GPIO_PORT_F	// Port F
#define	LED_PIN_I2C			GPIO_PIN_2	// PF2
#define	LED_PORT_WIFI		GPIO_PORT_F	// Port F
#define	LED_PIN_WIFI		GPIO_PIN_3	// PF3
#define	LED_PORT_BUZZ		GPIO_PORT_E	// Port E
#define	LED_PIN_BUZZ		GPIO_PIN_0	// PE0

#define	port(x)				(LED_PORT_##x)	// Get port name
#define	pin(x)				(LED_PIN_##x)	// Get pin name
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
static void	ledState(uint32_t port, uint8_t pin, bool state)
{
	if(state)	gpioHigh(port, pin);
	else		gpioLow(port, pin);
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
 *	Input		:
 *	Output		:
 *	Description	:
 */
 uint32_t	edmcLedSetup(void)
 {
	 /* Setup */
	 gpioOutputSetup(port(KP)	, pin(KP));
	 gpioOutputSetup(port(LCD)	, pin(LCD));
	 gpioOutputSetup(port(KB)	, pin(KB));
	 gpioOutputSetup(port(SDC)	, pin(SDC));
	 gpioOutputSetup(port(ICDI)	, pin(ICDI));
	 gpioOutputSetup(port(UART)	, pin(UART));
	 gpioOutputSetup(port(SPI)	, pin(SPI));
	 gpioOutputSetup(port(I2C)	, pin(I2C));
	 gpioOutputSetup(port(WIFI)	, pin(WIFI));
	 gpioOutputSetup(port(BUZZ)	, pin(BUZZ));
	 
	 /* State */
	 gpioHigh(port(KP)	, pin(KP));
	 gpioHigh(port(LCD)	, pin(LCD));
	 gpioHigh(port(KB)	, pin(KB));
	 gpioHigh(port(SDC)	, pin(SDC));
	 gpioHigh(port(ICDI), pin(ICDI));
	 gpioHigh(port(UART), pin(UART));
	 gpioHigh(port(SPI)	, pin(SPI));
	 gpioHigh(port(I2C)	, pin(I2C));
	 gpioHigh(port(WIFI), pin(WIFI));
	 gpioLow(port(BUZZ)	, pin(BUZZ));
	 
	 /* Return */
	 return 0;
 }
//-------------------------------------------------------------------------------------------------
/*
 *	Input		:
 *	Output		:
 *	Description	:
 */
void	edmcLedState(tLed ui8Led, bool state)
{
	/* LED as low active, Buzzer as high active */
	switch(ui8Led)
	{
		case LED(KP)	:	ledState(port(KP)	, pin(KP)	, !state);	break;
		case LED(LCD)	:	ledState(port(LCD)	, pin(LCD)	, !state);	break;
		case LED(KB)	:	ledState(port(KB)	, pin(KB)	, !state);	break;
		case LED(SDC)	:	ledState(port(SDC)	, pin(SDC)	, !state);	break;
		case LED(ICDI)	:	ledState(port(ICDI)	, pin(ICDI)	, !state);	break;
		case LED(UART)	:	ledState(port(UART)	, pin(UART)	, !state);	break;
		case LED(SPI)	:	ledState(port(SPI)	, pin(SPI)	, !state);	break;
		case LED(I2C)	:	ledState(port(I2C)	, pin(I2C)	, !state);	break;
		case LED(WIFI)	:	ledState(port(WIFI)	, pin(WIFI)	, !state);	break;
		case LED(BUZZ)	:	ledState(port(BUZZ)	, pin(BUZZ)	, state);	break;
	}
}

