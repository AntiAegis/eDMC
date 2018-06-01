/*
 *	File		:	SDCARD.1.0.1.h
 *	Date		:	31/12/2016
 *	Author		:	Nguyen Chinh Thuy
 *	Language	: 	C
 *	IDE			:	CCS7.0.0.00042
 *	Object		:	TIVAC1294NCPDT
 *	Version		:	1.0.1
 *	Description	:	Source of SD Card
 */
/**************************************************************************************************
 *	INCLUDEs
 *************************************************************************************************/
#include "SDCARD.1.0.1.h"


/**************************************************************************************************
 *	PUBLIC
 *************************************************************************************************/
FRESULT		varFresult;


/**************************************************************************************************
 *	PRIVATE
 *************************************************************************************************/
static FATFS 		sFatFs;						// File system object
static DIR 			sDirObject;					//
//static FILINFO 		sFileInfo;				//
static FIL 			sFileObject;				//
static char 		strCurrDir[SDC_PATH_NUM];	// Current Directory


/**************************************************************************************************
 *	FUNCTION
 *************************************************************************************************/
/*
 * Function	:	sdcMount
 * Purpose	:	Mount disk (Just support for single disk)
 * Input	:	varVol:	Logical drive number
 * 				pFs: Address of a FAT file system object
 * Output	:
 */
FRESULT	sdcMount(uint8_t varVol)
{
	return	f_mount(varVol, &sFatFs);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function	:	sdcardChangeDir
 * Purpose	:	Specife the directory to make the current working directory. Path separators must
 * 						use a forward slash "/".  The argument to cd can be one of the following:
 * 						* root ("/")
 * 						* a fully specified path ("/my/path/to/mydir")
 * 						* a single directory name that is in the current directory ("mydir")
 * 						* parent directory ("../")
 * 						It does not understand relative paths, so dont try something like this:
 * 						("../my/new/path")
 * 						Once the new directory is specified, it attempts to open the directory to make sure
 * 						it exists. If the new path is opened successfully, then the current working
 * 						directory is changed to the new path.
 * 						In cases of error, the pui32Reason parameter will be written with one of the
 * 						following values
 * Input	:	strPath: Path
 * 				pReason: Address to store reason
 * Output	:
 */
FRESULT	sdcChangeDir(char strPath[])
{
	/* Declare */
	uint32_t 	ui32Idx;
	FRESULT 	iFResult;
	char		strTmpBuff[SDC_PATH_NUM];

	/* Copy the current directory into temporary buffer */
	strcpy(strTmpBuff, strCurrDir);

	/* If first character is /, it is fully specified path, it should just be used as-is */
	if(strPath[0] == '/')
	{
		/* Make sure the new path is not bigger than the cwd buffer */
		if(strlen(strPath) + 1 > sizeof(strCurrDir))	return FR_INVALID_NAME;

		/* If the new path name is not too long, copy it into the temporary buffer */
		else strncpy(strTmpBuff, strPath, sizeof(strTmpBuff));
	}

	/* If the argument is .., attempt to remove the lowest level on the CWD */
	else if(strcmp(strPath, "../") == 0)
	{
		/* Get the index to the last character in the current path */
		ui32Idx = strlen(strTmpBuff) - 1;

		/* Back up from the end of the path name until a separator (/) is found, or until we bump
		   up to the start of the path */
		while((strTmpBuff[ui32Idx] != '/') && (ui32Idx > 1)) ui32Idx--;	// Back up one character

		/* Now we are either at the lowest level separator in the current path, or at the beginning
		   of the string (root).  So set the new end of string here, effectively removing that last
		   part of the path */
		strTmpBuff[ui32Idx] = 0;
	}

	/* Otherwise this is just a normal path name from the current directory, and it needs to be
	   appended to the current path */
	else
	{
		/* Check whether strCurrDir has enough size */
		if(strlen(strTmpBuff) + strlen(strPath) + 1 + 1 > sizeof(strCurrDir))
			return FR_INVALID_NAME;

		/* If enough size, add '/' and append the new directory to the path */
		else
		{
			/* If not already at the root level, then append a '/' */
			if(strcmp(strTmpBuff, "/"))		strcat(strTmpBuff, "/");

			/* Append the new directory to the path */
			strcat(strTmpBuff, strPath);
		}
	}

	/* New directory path is in strTmpBuff.  Try to open it to make sure it is valid */
	iFResult = f_opendir(&sDirObject, strTmpBuff);

	/* If it can't be opened, then it is a bad path.  Inform the user and return */
	if(iFResult != FR_OK)	return iFResult;

	/* Otherwise, it is a valid new path, so copy it into the CWD and update the screen */
	else strncpy(strCurrDir, strTmpBuff, sizeof(strCurrDir));

	/* Return success */
	return FR_OK;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function	:	sdcFileOpen
 * Purpose	:	Open a file
 * Input	:	strFName: Name of file
 * Output	:
 */
FRESULT	sdcFileOpen(char strFName[])
{
	/* Declare */
    char	strTmpBuff[SDC_PATH_NUM];		// Temporary buffer string

    /* Check whether too long string */
    if(strlen(strCurrDir) + strlen(strFName) + 2 > sizeof(strTmpBuff))
    	return FR_INVALID_NAME;

    /* Copy current directory to temporary buffer */
    strcpy(strTmpBuff, strCurrDir);

    /* If not already at the root level, then append a separator */
    if(strcmp("/", strCurrDir)) 	strcat(strTmpBuff, "/");

    /* Append file name to temporary buffer */
    strcat(strTmpBuff, strFName);

    /* Try to open file and return */
    return	f_open(&sFileObject, strTmpBuff, FA_READ);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function	:	sdcFileClose
 * Purpose	:	Close a file
 * Input	:	strFName: Name of file
 * Output	:
 */
FRESULT	sdcFileClose(char strFName[])
{
	/* Declare */
    char	strTmpBuff[SDC_PATH_NUM];		// Temporary buffer string

    /* Check whether too long string */
    if(strlen(strCurrDir) + strlen(strFName) + 2 > sizeof(strTmpBuff))
    	return FR_INVALID_NAME;

    /* Copy current directory to temporary buffer */
    strcpy(strTmpBuff, strCurrDir);

    /* If not already at the root level, then append a separator */
    if(strcmp("/", strCurrDir)) 	strcat(strTmpBuff, "/");

    /* Append file name to temporary buffer */
    strcat(strTmpBuff, strFName);

    /* Try to close file and return */
    return	f_close(&sFileObject);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function	:	sdcReadFile
 * Purpose	:	Read data from file (File must be openned by function "sdcFileOpen" before)
 * Input	:	arrGetData: array to get data
 * 				varLength: Number of byte to read
 * Output	:
 */
FRESULT	sdcFileRead(uint8_t arrGetData[], uint16_t varLength)
{
	/* Declare */
	FRESULT 	iFResult;					// Result of FATS
	uint32_t 	ui32BytesRead;				// Number of read bytes

	/* Read a block of data */
	iFResult = f_read(&sFileObject, arrGetData, varLength - 1, (UINT*)&ui32BytesRead);

	/* If there was an error reading, then print a newline and return the error to the user */
	if(iFResult != FR_OK)	return iFResult;

	/* Add null character to terminate temporary string */
	arrGetData[ui32BytesRead] = 0;

	/* Return success */
	return FR_OK;
}
//-------------------------------------------------------------------------------------------------
/*
 * Function	:
 * Purpose	:
 * Input	:
 * Output	:
 */
const char*	sdcNotifyStr(FRESULT iFResult)
{
	/* Declare */
	static char	arrFresult[20][23] =
	{
		SDC_GET_STR(FR_OK), SDC_GET_STR(FR_DISK_ERR), SDC_GET_STR(FR_INT_ERR),
		SDC_GET_STR(FR_NOT_READY), SDC_GET_STR(FR_NO_FILE), SDC_GET_STR(FR_NO_PATH),
		SDC_GET_STR(FR_INVALID_NAME), SDC_GET_STR(FR_DENIED), SDC_GET_STR(FR_EXIST),
		SDC_GET_STR(FR_INVALID_OBJECT), SDC_GET_STR(FR_WRITE_PROTECTED),
		SDC_GET_STR(FR_INVALID_DRIVE), SDC_GET_STR(FR_NOT_ENABLED), SDC_GET_STR(FR_NO_FILESYSTEM),
		SDC_GET_STR(FR_MKFS_ABORTED), SDC_GET_STR(FR_TIMEOUT), SDC_GET_STR(FR_LOCKED),
		SDC_GET_STR(FR_NOT_ENOUGH_CORE), SDC_GET_STR(FR_TOO_MANY_OPEN_FILES),
		SDC_GET_STR(FR_INVALID_PARAMETER)
	};

	/* Return */
	return(const char*)(&arrFresult[iFResult][3]);
}
//-------------------------------------------------------------------------------------------------
/*
 * Function	:
 * Purpose	:
 * Input	:
 * Output	:
 */
//-------------------------------------------------------------------------------------------------

