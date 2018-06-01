/*
 *	Date		:	2017/01/27
 *	Author		:	Nguyen Chinh Thuy
 *	Version		:	1.0.1
 *	Description	:	Source file of Command Line
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
/* Standard */

/* Producer */

/* My */

/* This project */
#include "FIRMWARE/FIRMWARE.1.0.1.h"
#include "SOFTWARE/Command Line/SW.CMD.1.0.1.h"


/**************************************************************************************************
 *	PRIVATEs
 *************************************************************************************************/
/* Program Address */
#include "SOFTWARE/System Control/SW.SYSCTL.1.0.1.h"

static	tProgAddr	st_psProgAddr[] =			// Program must be registered at here
{
	{"SysCtl", fnSysCtl},
};
#define	PROG_NUM	(sizeof(st_psProgAddr) / sizeof(tProgAddr)) // Number of Program
static	uint8_t		st_ui8ProgAddrCount = 0;	// Current Program
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:	str 		: String name of Program needed to find
 *			 	pui8Prog	: Index of found program
 *	Output	:	True if matching Program name, False if not matching Program name
 *	Purpose	:	Find the Program coressponding with a string
 */
static	bool	findProg(char str[], uint8_t* pui8Prog)
{
	/* Declare */
	uint8_t	i;

	/* Find string */
	for(i = 0; i < PROG_NUM; i++)
	{
		if(!strcmp(str, st_psProgAddr[i].strProg))
		{
			*pui8Prog = i;
			return true;
		}
	}

	/* Return */
	return false;
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
#define	NAME2STR(x)		(#x)
static	void	resAnalysis(etProgRes PROG_RES)
{
	switch(PROG_RES)
	{
		case PROG_RES(OK_CMD):
			break;
		case PROG_RES(NULL_CMD):
			fwIdc("CmdLine: %s\n", NAME2STR(NULL_CMD));
			break;
		case PROG_RES(INVALID_CMD):
			fwIdc("CmdLine: %s\n", NAME2STR(INVALID_CMD));
			break;
		case PROG_RES(INVALID_PARA):
			fwIdc("CmdLine: %s\n", NAME2STR(INVALID_PARA));
			break;
		case PROG_RES(CANNOT_RUN_CMD):
			fwIdc("%s: %s\n", st_psProgAddr[st_ui8ProgAddrCount].strProg, NAME2STR(CANNOT_RUN_CMD));
			break;
		case PROG_RES(CHANGE_SOFTWARE):
			fwIdc("CmdLine: %s to %s\n", NAME2STR(CHANGE_SOFTWARE),
													st_psProgAddr[st_ui8ProgAddrCount].strProg);
			break;
	}
}


/**************************************************************************************************
 *	PUBLICs
 *************************************************************************************************/
/*
 *	Input	:
 *	Output	:
 *	Purpose	:
 */
void	swCmdStrPrc(char str[])
{
	/* Declare */
	uint8_t	tmp;
	uint8_t	pui8ArgPos[15];
	uint8_t	ui8ArgNum;
	
	/* Argument analysis */
	ui8ArgNum = swCmdArgList(str, pui8ArgPos);
	if(ui8ArgNum == 0)
	{
		resAnalysis(PROG_RES(NULL_CMD));
		return;
	}

	/* If in default program: System Control, the first word maybe other Program */
	if(st_ui8ProgAddrCount == 0)
	{
		/* If the first word is matched with another Program's name */
		if(findProg(&str[pui8ArgPos[0]], &tmp))
		{
			st_ui8ProgAddrCount = tmp;
			if(--ui8ArgNum)
			{
				resAnalysis(st_psProgAddr[tmp].pfn(str, &pui8ArgPos[1], ui8ArgNum));
				return;
			}
			else
			{
				resAnalysis(PROG_RES(CHANGE_SOFTWARE));
				return;
			}
		}
		
		/* If the first word is not matched with another Program's name */
		else
		{
			resAnalysis(st_psProgAddr[st_ui8ProgAddrCount].pfn(str, pui8ArgPos, ui8ArgNum));
			return;
		}
	}

	/* If not in default program (System Control) */
	else
	{
		resAnalysis(st_psProgAddr[st_ui8ProgAddrCount].pfn(str, pui8ArgPos, ui8ArgNum));
		return;
	}
}
//-------------------------------------------------------------------------------------------------
/*
 *	Input	:	str			: Command string
 *				pui8ArgPos	: Array to store position of starting of each argument
 *	Output	:	Number of arguments
 *	Purpose	:	List arguments of command string
 */
uint8_t
swCmdArgList(char str[], uint8_t* pui8ArgPos)
{
	/* Declare */
	uint8_t	i;
	uint8_t argNum = 0;
	uint8_t length = strlen(str);
	bool	isIdle = true;

	/* If a null string */
	if (!length)	return 0;

	/* For loop */
	for (i = 0; i < length; i++)
	{
		/* If meet idle character, set flag Idle */
		if ((str[i] == ' ') || (str[i] == '\t'))
		{
			str[i] = '\0';
			isIdle = true;	// Set flag Idle
		}

		/* If meet meaning character */
		else
		{
			/* If flag Idle is true, this means a new argument is found */
			if (isIdle)
			{
				pui8ArgPos[argNum++] = i;	// Save position and increase argNum
				isIdle = false;				// Clear flag Idle
			}
		}
	}

	/* Return */
	return argNum;
}

