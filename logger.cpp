/*
 * logger.cpp
 *
 *  Created on: 7 abr 2022
 *      Author: epinuela
 */

#include "logger.h"
#include <stdio.h>
#include <string.h>
#include <iostream>


/**
 * Defines
 */
#define SZ_LOGGER_LEVEL_STRING			8
#define SZ_LOGGER_TIMESTAMP				20
#define LOGGER_VERSION			"LOGGER 1.0"

Logger * Logger::m_pLoggerHandler = NULL;

typedef struct S_LOGGER_LEVEL_LOOKUP {
	ENUM_LOGGER_LEVEL eLevel;
	char * pcLevel;
}S_LOGGER_LEVEL_LOOKUP;

/**
 * Default constructor
 */
Logger::Logger ( void )
{
	// not implemented
}

/**
 * Default destructor
 */
Logger::~Logger ( void )
{
	// not implemented
}

/**
 * Generic log method
 */
void Logger::Log( ENUM_LOGGER_LEVEL i_eLevel, char * i_pcLogString )
{
	bool bLevelStringFound = false;
	char acLevel[SZ_LOGGER_LEVEL_STRING + 1] = {0};
	char acTime[SZ_LOGGER_TIMESTAMP + 1] = {0};

	///< Check function arguments
	if (	( EN_LOGGER_LEVEL_UNKNOWN > i_eLevel )
			|| ( EN_LOGGER_LEVEL_MAX < i_eLevel )
			|| ( NULL == i_pcLogString ) )
	{
		///< Invalid function argument
	}
	else
	{
		bLevelStringFound = GetLogLevelString(i_eLevel, acLevel, sizeof(acLevel) );
		if (bLevelStringFound)
		{
			GetDateTime(acTime);
			printf("%s\t[%s]\t%s", acTime, acLevel, i_pcLogString);
		}
	}
}

/**
 * Get string log level
 */
bool Logger::GetLogLevelString (ENUM_LOGGER_LEVEL i_eLevel, char * o_pcLevelString, unsigned int i_uiLevelStringSize )
{
	S_LOGGER_LEVEL_LOOKUP astLogLevelTable[]=
	{
		  { EN_LOGGER_LEVEL_USER	, (char *)"USER"		}
		, { EN_LOGGER_LEVEL_WARNING	, (char *)"WARNING"		}
		, { EN_LOGGER_LEVEL_ERROR	, (char *)"ERROR"		}
	};
	unsigned int uiNItems = sizeof(astLogLevelTable)/sizeof(astLogLevelTable[0]);
	unsigned int uiIndex  = 0;
	bool bRet = false;

	///< Check function arguments
	if (	( EN_LOGGER_LEVEL_UNKNOWN > i_eLevel )
			|| ( EN_LOGGER_LEVEL_MAX < i_eLevel )
			|| ( NULL == o_pcLevelString )
			|| ( !i_uiLevelStringSize ) )
	{
		///< Invalid function argument
	}
	else
	{
		for ( uiIndex = 0; uiIndex < uiNItems; uiIndex++ )
		{
			if ( astLogLevelTable[uiIndex].eLevel == i_eLevel )
			{
				strncpy(o_pcLevelString, (const char *)astLogLevelTable[uiIndex].pcLevel, i_uiLevelStringSize );
				bRet = true;
				break;
			}
		}
	}
	return bRet;
}

/**
 * Get current date and time
 */
void Logger::GetDateTime (char * o_pcDateTime )
{
	time_t     now = time(0);
	struct tm  stTime = {0};

	///< Check function arguments
	if (NULL == o_pcDateTime)
	{
		///< Invalid function argument
	}
	else
	{
		stTime = *localtime(&now);
		strftime(o_pcDateTime, sizeof(o_pcDateTime), "%Y-%m-%d.%X", &stTime);
	}
}

/**
 * Get interface method
 */
Logger * Logger::GetInterface ( void )
{
	if ( NULL == m_pLoggerHandler )
	{
		m_pLoggerHandler = new Logger();
	}

	return ( m_pLoggerHandler );
}

/**
 * User log
 */
void Logger::User ( char * i_pcLogString )
{
	Log(EN_LOGGER_LEVEL_USER, i_pcLogString);
}

/**
 * Warning log
 */
void Logger::Warning ( char * i_pcLogString )
{
	Log(EN_LOGGER_LEVEL_WARNING, i_pcLogString);
}

/**
 * Error log
 */
void Logger::Error ( char * i_pcLogString )
{
	Log(EN_LOGGER_LEVEL_ERROR, i_pcLogString);
}

/**
 * Get library version
 */
char * Logger::GetVersion( void )
{
	return (char *) LOGGER_VERSION;
}
