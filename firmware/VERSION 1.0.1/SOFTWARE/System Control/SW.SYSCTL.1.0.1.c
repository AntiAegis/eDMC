/*
 *	Date		:	2017/01/27
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of System Control
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "SOFTWARE/System Control/SW.SYSCTL.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Command */
static	tSysCtlCmd	st_sCmd[] = 
{
	{"help"		, cmdHelp},
	{"enable"	, cmdEnable},
	{"disable"	, cmdDisable},
	{"info"		, cmdInfo}
};
#define	CMD_NUM			(sizeof(st_sCmd) / sizeof(tSysCtlCmd))
/*
 *	Input	:	str 		: Command string needed to find
 *				pui8Index	: Index of command matched if found
 *	Output	:	True if found, False if not found
 *	Purpose	:	Find command
 */
static	bool	findCmd(char str[], uint8_t* pui8Index)
{
	/* Declare */
	uint8_t i;

	/* Find */
	for(i = 0; i < CMD_NUM; i++)
	{
		if(!strcmp(str, st_sCmd[i].strCmd))
		{
			*pui8Index = i;
			return true;
		}
	}

	/* Return */
	return false;
}
//-------------------------------------------------------------------------------------------------
/* Component */
static	tSysCtlCpnt		st_sCpnt[] = 
{
	{true , CPNT_STT(RUNNING)	, 0},	// 0: kp
	{true , CPNT_STT(RUNNING)	, 0},	// 1: lcd
	{true , CPNT_STT(IDLE)		, 0},	// 2: kb
	{true , CPNT_STT(IDLE)		, 0},	// 3: sdc
	{true , CPNT_STT(IDLE)		, 0},	// 4: icdi
	{false, CPNT_STT(NOT_AVAI)	, 0},	// 5: uart
	{false, CPNT_STT(NOT_AVAI)	, 0},	// 6: spi
	{false, CPNT_STT(NOT_AVAI)	, 0},	// 7: i2c
	{false, CPNT_STT(NOT_AVAI)	, 0},	// 8: wifi
};
#define	IDX_KP 			0
#define	IDX_LCD 		1
#define	IDX_KB 			2
#define	IDX_SDC 		3
#define	IDX_ICDI		4
#define	IDX_UART		5
#define	IDX_SPI			6
#define	IDX_I2C			7
#define	IDX_WIFI		8
#define	IDX(x)			(IDX_##x)
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
static	etProgRes	cmdHelp(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum)
{
	/* No parameter is required */
	if(ui8ArgNum)	return	PROG_RES(INVALID_PARA);
	
	/* Indicator */
	fwIdc("**************************************************\n");
	fwIdc("Help of software \"System Control\":\n"				);
	fwIdc("\n>> Command available <<\n"							);
	fwIdc("help, enable, disable, info\n"						);
	fwIdc("\n>> Component available <<\n"						);
	fwIdc("kp, lcd, kb, sdc, icdi, uart, spi, i2c, wifi\n"		);
	fwIdc("**************************************************\n");

	/* Return */
	return PROG_RES(OK_CMD);
}
//-------------------------------------------------------------------------------------------------
 /*
  *	Input	:
  *	Output	:
  *	Purpose	:
  */
static	etProgRes	cmdEnable(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum)
{
	/* One parameter is required */
	if(ui8ArgNum != 1)	return	PROG_RES(INVALID_PARA);

	/* Process */
	if(!strcmp(&str[pui8ArgPos[0]], "kp"))
	{
		fwIdc("SysCtl: kp is primarily enabled\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "lcd"))
	{
		if(st_sCpnt[IDX(LCD)].isEn)	fwIdc("SysCtl: lcd was enabled before\n");
		else
		{
			fwLcdEnable;
			st_sCpnt[IDX(LCD)].isEn = true;
			st_sCpnt[IDX(LCD)].STT = CPNT_STT(RUNNING);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "kb"))
	{
		if(st_sCpnt[IDX(KB)].isEn)	fwIdc("SysCtl: kb was enabled before\n");
		else
		{
			fwKbEnable;
			st_sCpnt[IDX(KB)].isEn = true;
			st_sCpnt[IDX(KB)].STT = CPNT_STT(RUNNING);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "sdc"))
	{
		if(st_sCpnt[IDX(SDC)].isEn)	fwIdc("SysCtl: sdc was enabled before\n");
		else
		{
			fwSdcEnable;
			st_sCpnt[IDX(SDC)].isEn = true;
			st_sCpnt[IDX(SDC)].STT = CPNT_STT(RUNNING);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "icdi"))
	{
		if(st_sCpnt[IDX(ICDI)].isEn)	fwIdc("SysCtl: icdi was enabled before\n");
		else
		{
			fwIcdiEnable;
			st_sCpnt[IDX(ICDI)].isEn = true;
			st_sCpnt[IDX(ICDI)].STT = CPNT_STT(RUNNING);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "uart"))
	{
		if(st_sCpnt[IDX(UART)].isEn)	fwIdc("SysCtl: uart was enabled before\n");
		else
		{
			fwUartEnable;
			st_sCpnt[IDX(UART)].isEn = true;
			st_sCpnt[IDX(UART)].STT = CPNT_STT(IDLE);
			fwUartSend("TM4C1294NCPDT\n", 1, 0);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "spi"))
	{
		if(st_sCpnt[IDX(SPI)].isEn)	fwIdc("SysCtl: spi was enabled before\n");
		else
		{
			fwSpiEnable;
			st_sCpnt[IDX(SPI)].isEn = true;
			st_sCpnt[IDX(SPI)].STT = CPNT_STT(IDLE);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "i2c"))
	{
		if(st_sCpnt[IDX(I2C)].isEn)	fwIdc("SysCtl: i2c was enabled before\n");
		else
		{
			fwI2cEnable;
			st_sCpnt[IDX(I2C)].isEn = true;
			st_sCpnt[IDX(I2C)].STT = CPNT_STT(IDLE);
		}
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "wifi"))
	{
		if(st_sCpnt[IDX(WIFI)].isEn)	fwIdc("SysCtl: wifi was enabled before\n");
		else
		{
			fwWifiEnable;
			st_sCpnt[IDX(WIFI)].isEn = true;
			st_sCpnt[IDX(WIFI)].STT = CPNT_STT(IDLE);
		}
		return 	PROG_RES(OK_CMD);
	}

	/* Return */
	return 	PROG_RES(INVALID_PARA);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
static	etProgRes	cmdDisable(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum)
{
	/* One parameter is required */
	if(ui8ArgNum != 1)	return	PROG_RES(INVALID_PARA);

	/* Process */
	if(!strcmp(&str[pui8ArgPos[0]], "kp"))
	{
		return 	PROG_RES(CANNOT_RUN_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "lcd"))
	{
		if(st_sCpnt[IDX(LCD)].isEn)
		{
			fwLcdDisable;
			st_sCpnt[IDX(LCD)].isEn = false;
			st_sCpnt[IDX(WIFI)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: lcd hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "kb"))
	{
		if(st_sCpnt[IDX(KB)].isEn)
		{
			fwKbDisable;
			st_sCpnt[IDX(KB)].isEn = false;
			st_sCpnt[IDX(KB)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: kb hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "sdc"))
	{
		if(st_sCpnt[IDX(SDC)].isEn)
		{
			fwSdcDisable;
			st_sCpnt[IDX(SDC)].isEn = false;
			st_sCpnt[IDX(SDC)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: sdc hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "icdi"))
	{
		if(st_sCpnt[IDX(ICDI)].isEn)
		{
			fwIcdiDisable;
			st_sCpnt[IDX(ICDI)].isEn = false;
			st_sCpnt[IDX(ICDI)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: icdi hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "uart"))
	{
		if(st_sCpnt[IDX(UART)].isEn)
		{
			fwUartDisable;
			st_sCpnt[IDX(UART)].isEn = false;
			st_sCpnt[IDX(UART)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: uart hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "spi"))
	{
		if(st_sCpnt[IDX(SPI)].isEn)
		{
			fwSpiDisable;
			st_sCpnt[IDX(SPI)].isEn = false;
			st_sCpnt[IDX(SPI)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: spi hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "i2c"))
	{
		if(st_sCpnt[IDX(I2C)].isEn)
		{
			fwI2cDisable;
			st_sCpnt[IDX(I2C)].isEn = false;
			st_sCpnt[IDX(I2C)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: i2c hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "wifi"))
	{
		if(st_sCpnt[IDX(WIFI)].isEn)
		{
			fwWifiDisable;
			st_sCpnt[IDX(WIFI)].isEn = false;
			st_sCpnt[IDX(WIFI)].STT = CPNT_STT(NOT_AVAI);
		}
		else	fwIdc("SysCtl: wifi hasn't been enabled yet\n");
		return 	PROG_RES(OK_CMD);
	}
	
	/* Return */
	return PROG_RES(INVALID_PARA);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
static	etProgRes	cmdInfo(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum)
{
	/* One parameter is required */
	if(ui8ArgNum != 1)	return	PROG_RES(INVALID_PARA);

	/* Process */
	if(!strcmp(&str[pui8ArgPos[0]], "kp"))
	{
		infoPrint(IDX(KP));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "lcd"))
	{
		infoPrint(IDX(LCD));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "kb"))
	{
		infoPrint(IDX(KB));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "sdc"))
	{
		infoPrint(IDX(SDC));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "icdi"))
	{
		infoPrint(IDX(ICDI));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "uart"))
	{
		infoPrint(IDX(UART));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "spi"))
	{
		infoPrint(IDX(SPI));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "i2c"))
	{
		infoPrint(IDX(I2C));
	}
	else if(!strcmp(&str[pui8ArgPos[0]], "wifi"))
	{
		infoPrint(IDX(WIFI));
	}

	/* Return */
	return PROG_RES(INVALID_PARA);
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
#define	NAME2STR(x)			(#x)
static	void	infoPrint(uint8_t IDX_)
{
	/* Pre-fix */
	fwIdc("SysCtl: ");

	/* Switch */
	switch(IDX_)
	{
	case IDX(KP):
		fwIdc("kp {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(KP)].isEn,
			  st_sCpnt[IDX(KP)].STT,
			  st_sCpnt[IDX(KP)].ui32Mem);
		break;
	case IDX(LCD):
		fwIdc("lcd {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(LCD)].isEn,
			  st_sCpnt[IDX(LCD)].STT,
			  st_sCpnt[IDX(LCD)].ui32Mem);
		break;
	case IDX(KB):
		fwIdc("kb {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(KB)].isEn,
			  st_sCpnt[IDX(KB)].STT,
			  st_sCpnt[IDX(KB)].ui32Mem);
		break;
	case IDX(SDC):
		fwIdc("sdc {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(SDC)].isEn,
			  st_sCpnt[IDX(SDC)].STT,
			  st_sCpnt[IDX(SDC)].ui32Mem);
		break;
	case IDX(ICDI):
		fwIdc("icdi {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(ICDI)].isEn,
			  st_sCpnt[IDX(ICDI)].STT,
			  st_sCpnt[IDX(ICDI)].ui32Mem);
		break;
	case IDX(UART):
		fwIdc("uart {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(UART)].isEn,
			  st_sCpnt[IDX(UART)].STT,
			  st_sCpnt[IDX(UART)].ui32Mem);
		break;
	case IDX(SPI):
		fwIdc("spi {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(SPI)].isEn,
			  st_sCpnt[IDX(SPI)].STT,
			  st_sCpnt[IDX(SPI)].ui32Mem);
		break;
	case IDX(I2C):
		fwIdc("i2c {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(I2C)].isEn,
			  st_sCpnt[IDX(I2C)].STT,
			  st_sCpnt[IDX(I2C)].ui32Mem);
		break;
	case IDX(WIFI):
		fwIdc("wifi {isEn=%u, stt=%d, mem=%u}\n",
			  st_sCpnt[IDX(WIFI)].isEn,
			  st_sCpnt[IDX(WIFI)].STT,
			  st_sCpnt[IDX(WIFI)].ui32Mem);
		break;
	}
}


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/* Implementing function of SysCtl */
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
etProgRes	fnSysCtl(char str[], uint8_t* pui8ArgPos, uint8_t ui8ArgNum)
{
	/* Declare */
	uint8_t		index;

	/* Find command */
	if(findCmd(&str[pui8ArgPos[0]], &index))
	{
		if(--ui8ArgNum)	return	st_sCmd[index].pfn(str, &pui8ArgPos[1], ui8ArgNum);
		else			return	st_sCmd[index].pfn(str, 0, 0);
	}

	/* Return */
	return PROG_RES(INVALID_CMD);
}

