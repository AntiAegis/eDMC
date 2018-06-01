/*
 *	File			:	SSI.1.0.1.h
 *	Date created	:	28/12/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Header of SSI
 */
/**************************************************************************************************
 *	PRE-DEFINITIONs
 *************************************************************************************************/
#ifndef SSI_1_0_1_H_
#define SSI_1_0_1_H_


/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard Library */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

/* Producing Library */
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_ssi.h"

#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"

/* My Library */
#include "LAUNCHPAD.1.0.1.h"
#include "GPIO.1.0.1.h"


/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Module */
#define	SSI_MODULE_0			SSI0_BASE
#define	SSI_MODULE_1			SSI1_BASE
#define	SSI_MODULE_2			SSI2_BASE
#define	SSI_MODULE_3			SSI3_BASE

/* PROTOCOL */
#define	SSI_PROTO_MOTO_0		SSI_FRF_MOTO_MODE_0	// Moto fmt, polarity 0, phase 0
#define	SSI_PROTO_MOTO_1		SSI_FRF_MOTO_MODE_1	// Moto fmt, polarity 0, phase 1
#define	SSI_PROTO_MOTO_2		SSI_FRF_MOTO_MODE_2	// Moto fmt, polarity 1, phase 0
#define	SSI_PROTO_MOTO_3		SSI_FRF_MOTO_MODE_3	// Moto fmt, polarity 1, phase 1
#define	SSI_PROTO_TI			SSI_FRF_TI			// TI frame format
#define	SSI_PROTO_NMW			SSI_FRF_NMW			// National MicroWire frame format

/* Interrupt */
#define	SSI_INT_TXFF			SSI_TXFF			// TX FIFO half full or less
#define	SSI_INT_RXFF			SSI_RXFF			// RX FIFO half full or more
#define	SSI_INT_RXTO			SSI_RXTO			// RX timeout
#define	SSI_INT_RXOR			SSI_RXOR			// RX overrun


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
bool
ssiSetup		(uint32_t SSI_MODULE_, uint32_t varClkFreq, uint32_t SSI_PROTO_,
									uint32_t SSI_MODE_, uint32_t varBitRate, uint8_t varDataWidth);
void
ssiEnableModule	(uint32_t SSI_MODULE_);
void
ssiMuxGPIO		(uint32_t SSI_MODULE_);

/* Interrupt */
void
ssiIntSetup		(uint32_t SSI_MODULE_, uint32_t SSI_INT_, void (*pfnHandler)(void));
void
SSI_ISR(void);		// Put in main.c

/* Send and Get */
void
ssiSendChar		(uint32_t SSI_MODULE_, uint8_t varData);
void
ssiSendStr		(uint32_t SSI_MODULE_, uint8_t arrData[], uint16_t varLength);
uint32_t
ssiGetChar		(uint32_t SSI_MODULE_);
void
ssiGetStr		(uint32_t SSI_MODULE_, uint32_t arrData[]);


/**************************************************************************************************
 *	END OF SSI.1.0.1.h
 *************************************************************************************************/
#endif /* SSI_1_0_1_H_ */
