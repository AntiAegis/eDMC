/*
 *	File			:	I2C.1.0.1.h
 *	Date created	:	12/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Library of I2C
 */
#ifndef I2C_1_0_1_H_
#define I2C_1_0_1_H_
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
 /* Standard Library */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "string.h"

 /* Producing Library */
#include "inc/hw_ints.h"
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"

 /* My Library */
#include "LAUNCHPAD.1.0.1.h"
 
 /* This project */
 

/**************************************************************************************************
 *	DEFINITIONs
 *************************************************************************************************/
/* Module */
#define		I2C_MODULE_0			I2C0_BASE		// PB2_SCL, PB3_SDA
#define		I2C_MODULE_1			I2C1_BASE		// PG0_SCL, PG1_SDA
#define		I2C_MODULE_2			I2C2_BASE		// PL1_SCL, PL0_SDA
#define		I2C_MODULE_3			I2C3_BASE		// PK4_SCL, PK5_SDA
#define		I2C_MODULE_4			I2C4_BASE		// PK6_SCL, PK7_SDA
#define		I2C_MODULE_5			I2C5_BASE		// PB0_SCL, PB1_SDA
#define		I2C_MODULE_6			I2C6_BASE		// PA6_SCL, PA7_SDA
#define		I2C_MODULE_7			I2C7_BASE		// PD0_SCL, PD1_SDA
#define		I2C_MODULE_8			I2C8_BASE		// PD2_SCL, PD3_SDA
#define		I2C_MODULE_9			I2C9_BASE		// PA0_SCL, PA1_SDA

//-------------------------------------------------------------------------------------------------
/* Rate */
#define		I2C_RATE_100_KBPS		0				// Rate = 100 	Kbps
#define		I2C_RATE_400_KBPS		1				// Rate = 400 	Kbps
#define		I2C_RATE_1_MBPS			2				// Rate = 1 	Mbps
#define		I2C_RATE_3_3_MBPS		3				// Rate = 3.3	Mbps


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/* Setup */
void
i2cMstSetup 		(uint32_t I2C_MODULE_, uint32_t varClkFreq, uint32_t I2C_RATE_);

//-------------------------------------------------------------------------------------------------
/* Send */
uint32_t
i2cMstSendByte 		(uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t varData);
uint32_t
i2cMstSendArr 		(uint32_t I2C_MODULE_, uint8_t varSlvAddr,
														uint8_t arrData[], uint8_t varLength);

//-------------------------------------------------------------------------------------------------
/* Receive */
uint32_t
i2cMstReceiveByte 	(uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t varSlvReg, uint8_t *pStore);
uint32_t
i2cMstReceiveArr 	(uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t varSlvReg,
														uint8_t arrStore[], uint8_t varLength);


/**************************************************************************************************
 *	END OF I2C.1.0.1.h
 *************************************************************************************************/
#endif /* I2C_1_0_1_H_ */
