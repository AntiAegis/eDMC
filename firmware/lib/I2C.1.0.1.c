/*
 *	File			:	I2C.1.0.1.c
 *	Date created	:	12/10/2016
 *	Author			:	Nguyen Chinh Thuy
 *	Language		: 	C
 *	IDE				:	CCS6.1.2.00015
 *	Target object	:	TIVAC1294NCPDT
 *	Current version	:	1.0.1
 *	Description		:	Library of I2C
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
  /* Standard Library */
 
 /* Producing Library */
 
 /* My Library */
 
 /* This project */
#include "I2C.1.0.1.h"


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
 
 
 /**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/


/**************************************************************************************************
 *	FUNCTIONs
 *************************************************************************************************/
/*
 *	Function:	i2cSetup
 *	Purpose	:	Setup I2C
 *	Input	:	I2C_MODULE_: Which module of I2C (9:0)?
 *				varClkFreq: Clock frequency for I2C
 *				I2C_RATE_: Rate of I2C
 *	Output	:	None
 */
void
i2cMstSetup (uint32_t I2C_MODULE_, uint32_t varClkFreq, uint32_t I2C_RATE_)
{
	switch (I2C_MODULE_)
	{
		case I2C_MODULE_0:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);			// Enable I2C_0 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);		// Enable GPIO_B module
		    GPIOPinConfigure(GPIO_PB2_I2C0SCL);					// Configure pin I2C0SCL
		    GPIOPinConfigure(GPIO_PB3_I2C0SDA);					// Configure pin I2C0SDA
		    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_2 | GPIO_PIN_3);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_1:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);			// Enable I2C_1 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);		// Enable GPIO_G module
		    GPIOPinConfigure(GPIO_PG0_I2C1SCL);					// Configure pin I2C1SCL
		    GPIOPinConfigure(GPIO_PG1_I2C1SDA);					// Configure pin I2C1SDA
		    GPIOPinTypeI2C(GPIO_PORTG_BASE, GPIO_PIN_0 | GPIO_PIN_1);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTG_BASE, GPIO_PIN_0);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_2:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C2);			// Enable I2C_2 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);		// Enable GPIO_L module
		    GPIOPinConfigure(GPIO_PL1_I2C2SCL);					// Configure pin I2C2SCL
		    GPIOPinConfigure(GPIO_PL0_I2C2SDA);					// Configure pin I2C2SDA
		    GPIOPinTypeI2C(GPIO_PORTL_BASE, GPIO_PIN_1 | GPIO_PIN_0);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTL_BASE, GPIO_PIN_1);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_3:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C3);			// Enable I2C_3 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);		// Enable GPIO_K module
		    GPIOPinConfigure(GPIO_PK4_I2C3SCL);					// Configure pin I2C3SCL
		    GPIOPinConfigure(GPIO_PK5_I2C3SDA);					// Configure pin I2C3SDA
		    GPIOPinTypeI2C(GPIO_PORTK_BASE, GPIO_PIN_4 | GPIO_PIN_5);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTK_BASE, GPIO_PIN_4);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_4:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C4);			// Enable I2C_4 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);		// Enable GPIO_K module
		    GPIOPinConfigure(GPIO_PK6_I2C4SCL);					// Configure pin I2C4SCL
		    GPIOPinConfigure(GPIO_PK7_I2C4SDA);					// Configure pin I2C4SDA
		    GPIOPinTypeI2C(GPIO_PORTK_BASE, GPIO_PIN_6 | GPIO_PIN_7);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTK_BASE, GPIO_PIN_6);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_5:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C5);			// Enable I2C_5 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);		// Enable GPIO_B module
		    GPIOPinConfigure(GPIO_PB0_I2C5SCL);					// Configure pin I2C5SCL
		    GPIOPinConfigure(GPIO_PB1_I2C5SDA);					// Configure pin I2C5SDA
		    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_0);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_6:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C6);			// Enable I2C_6 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);		// Enable GPIO_A module
		    GPIOPinConfigure(GPIO_PA6_I2C6SCL);					// Configure pin I2C6SCL
		    GPIOPinConfigure(GPIO_PA7_I2C6SDA);					// Configure pin I2C6SDA
		    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_6 | GPIO_PIN_7);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_7:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C7);			// Enable I2C_7 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);		// Enable GPIO_D module
		    GPIOPinConfigure(GPIO_PD0_I2C7SCL);					// Configure pin I2C7SCL
		    GPIOPinConfigure(GPIO_PD1_I2C7SDA);					// Configure pin I2C7SDA
		    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_0);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_8:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C8);			// Enable I2C_8 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);		// Enable GPIO_D module
		    GPIOPinConfigure(GPIO_PD2_I2C8SCL);					// Configure pin I2C8SCL
		    GPIOPinConfigure(GPIO_PD3_I2C8SDA);					// Configure pin I2C8SDA
		    GPIOPinTypeI2C(GPIO_PORTD_BASE, GPIO_PIN_2 | GPIO_PIN_3);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTD_BASE, GPIO_PIN_2);		// Configure SCL pin for I2C
			break;
		case I2C_MODULE_9:
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C9);			// Enable I2C_9 module
		    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);		// Enable GPIO_A module
		    GPIOPinConfigure(GPIO_PA0_I2C9SCL);					// Configure pin I2C9SCL
		    GPIOPinConfigure(GPIO_PA1_I2C9SDA);					// Configure pin I2C9SDA
		    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
		    													// Configure pin for I2C
		    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_0);		// Configure SCL pin for I2C
			break;
	}

	HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;				// Clear I2C FIFOs

	I2CMasterEnable(I2C_MODULE_);								// Enable I2C module as Master

	switch (I2C_RATE_)
	{
		case I2C_RATE_100_KBPS:
			I2CMasterInitExpClk(I2C_MODULE_, varClkFreq, false);
			break;
		case I2C_RATE_400_KBPS:
			I2CMasterInitExpClk(I2C_MODULE_, varClkFreq, true);
			break;
		case I2C_RATE_1_MBPS:
			I2CMasterInitExpClk(I2C_MODULE_, varClkFreq, true);
			// Not completely
			break;
		case I2C_RATE_3_3_MBPS:
			I2CMasterInitExpClk(I2C_MODULE_, varClkFreq, true);
			// Not completely
			break;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	i2cMstSendByte
 *	Purpose	:	Master send a byte data
 *	Input	:	I2C_MODULE_: Which module of I2C (9:0)?
 *				varSlvAddr: Address of slave
 *				varData: Byte of data to be sent by Master
 *	Output	:	None
 */
uint32_t
i2cMstSendByte (uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t varData)
{
	while(I2CMasterBusBusy(I2C_MODULE_));				// Poll whether Bus is busy?
	//=============================================================================================
	I2CMasterSlaveAddrSet(I2C_MODULE_, varSlvAddr, false);
														// Set slave address and send direction
	I2CMasterDataPut(I2C_MODULE_, varData);				// Send a byte of data

	I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_SINGLE_SEND);
														// Single send transaction
	//=============================================================================================
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	return 1;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	i2cMstSendArr
 *	Purpose	:	Master send an array data
 *	Input	:	I2C_MODULE_: Which module of I2C (9:0)?
 *				varSlvAddr: Address of slave
 *				arrData: Array of data to be sent by Master
 *	Output	:	None
 */
uint32_t
i2cMstSendArr (uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t arrData[], uint8_t varLength)
{
	/* Declare */
	uint8_t varTmpCount = 0;
	
	while(I2CMasterBusBusy(I2C_MODULE_));				// Poll whether Bus is busy?
	//=============================================================================================
	I2CMasterSlaveAddrSet(I2C_MODULE_, varSlvAddr, false);
														// Set slave address and send direction
	I2CMasterDataPut(I2C_MODULE_, arrData[0]);			// Send the first byte data of array
	I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_BURST_SEND_START);
														// Start burst send transaction
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	//=============================================================================================
	for(varTmpCount = 1; varTmpCount < (varLength - 1); varTmpCount++)
	{
		I2CMasterDataPut(I2C_MODULE_, arrData[varTmpCount]);
														// Send data of array
		I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_BURST_SEND_CONT);
														// Continue burst send transaction
		while(I2CMasterBusy(I2C_MODULE_));				// Poll whether Master is busy?
	}
	//=============================================================================================
	I2CMasterDataPut(I2C_MODULE_, arrData[varLength-1]);
														// Send the last data of array
	I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_BURST_SEND_FINISH);
														// Finish burst send transaction
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	//=============================================================================================
	return 1;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	i2cMstReceiveByte
 *	Purpose	:	Master receive a byte data
 *	Input	:	I2C_MODULE_: Which module of I2C (9:0)?
 *				varSlvAddr: Address of slave
 *				pStore: Address of storing byte of data to be received by Master
 *	Output	:	None
 */
uint32_t
i2cMstReceiveByte (uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t varSlvReg, uint8_t *pStore)
{
	while(I2CMasterBusBusy(I2C_MODULE_));				// Poll whether Bus is busy?
	//=============================================================================================
	I2CMasterSlaveAddrSet(I2C_MODULE_, varSlvAddr, false);
														// Set slave address and send direction
	I2CMasterDataPut(I2C_MODULE_, varSlvReg);			// Send Slave's register want to be read
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
														// Send register address to Slave
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	//=============================================================================================
	I2CMasterSlaveAddrSet(I2C_MODULE_, varSlvAddr, true);
														// Set slave address and receive direction
	I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_SINGLE_RECEIVE);
														// Single receive transaction
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	*pStore = I2CMasterDataGet(I2C_MODULE_);			// Receive a byte of data
	//=============================================================================================
	return 1;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:	i2cMstReceiveArr
 *	Purpose	:	Master receive an array data
 *	Input	:	I2C_MODULE_: Which module of I2C (9:0)?
 *				varSlvAddr: Address of slave
 *				arrStore: Array of storing data to be received by Master
 *	Output	:	None
 */
uint32_t
i2cMstReceiveArr (uint32_t I2C_MODULE_, uint8_t varSlvAddr, uint8_t varSlvReg,
															uint8_t arrStore[], uint8_t varLength)
{
	/* Declare */
	uint8_t varTmpCount = 0;
	
	while(I2CMasterBusBusy(I2C_MODULE_));				// Poll whether Bus is busy?
	//=============================================================================================
	I2CMasterSlaveAddrSet(I2C_MODULE_, varSlvAddr, false);
														// Set slave address and send direction
	I2CMasterDataPut(I2C_MODULE_, varSlvReg);			// Send Slave's register want to be read
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
														// Send register address to Slave
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	//=============================================================================================
	I2CMasterSlaveAddrSet(I2C_MODULE_, varSlvAddr, true);
														// Set slave address and receive direction
	I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_BURST_RECEIVE_START);
														// Start multi-receive transaction
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	arrStore[0] = I2CMasterDataGet(I2C_MODULE_);		// Receive a byte of data
	//=============================================================================================
	for(varTmpCount = 1; varTmpCount < (varLength - 1); varTmpCount++)
	{
		I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
															// Continue multi-receive transaction
		while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
		arrStore[varTmpCount] = I2CMasterDataGet(I2C_MODULE_);
															// Receive a byte of data
	}
	//=============================================================================================
	I2CMasterControl(I2C_MODULE_, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
														// Finish multi-receive transaction
	while(I2CMasterBusy(I2C_MODULE_));					// Poll whether Master is busy?
	arrStore[varLength - 1] = I2CMasterDataGet(I2C_MODULE_);
														// Receive the last byte of data
	//=============================================================================================
	return 1;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------
/*
 *	Function:
 *	Purpose	:
 *	Input	:
 *	Output	:
 */
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
 *	END OF I2C.1.0.1.c
 *************************************************************************************************/
