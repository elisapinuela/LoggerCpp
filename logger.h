/*
 * logger.h
 *
 *  Created on: 7 abr 2022
 *      Author: epinuela
 */

#ifndef LOGGER_H_
#define LOGGER_H_


/**
 *
 */

/**
 * Logger levels enumeration
 */
typedef enum ENUM_LOGGER_LEVEL {
	EN_LOGGER_LEVEL_UNKNOWN = 0
	, EN_LOGGER_LEVEL_USER = 0
	, EN_LOGGER_LEVEL_WARNING
	, EN_LOGGER_LEVEL_ERROR
	///< Add new levels here
	, EN_LOGGER_LEVEL_MAX = 0xFFFFFFFF
}ENUM_LOGGER_LEVEL;

// C++ API //////////////////////////////////////////////////////////////////////
class Logger
{
private:
	static Logger * m_pLoggerHandler;

	/**
	 * Default constructor
	 */
	Logger ( void );

	/**
	 * Default destructor
	 */
	virtual ~Logger ( void );

	/**
	 * Generic log method
	 */
	void Log( ENUM_LOGGER_LEVEL i_eLevel, char * i_pcLogString );

	/**
	 * Get string log level
	 */
	static bool GetLogLevelString (ENUM_LOGGER_LEVEL i_eLevel, char * o_pcLevelString, unsigned int i_uiLevelStringSize );

	/**
	 * Get current date and time
	 */
	static void GetDateTime (char * o_pcDateTime );
public:
	/**
	 * Get interface method
	 */
	static Logger * GetInterface ( void );

	/**
	 * User log
	 */
	void User ( char * i_pcLogString );

	/**
	 * Warning log
	 */
	void Warning ( char * i_pcLogString );

	/**
	 * Error log
	 */
	void Error ( char * i_pcLogString );

	/**
	 * Get library version
	 */
	char * GetVersion( void );
};

// C API //////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C"  {
#endif		// __cplusplus



#ifdef __cplusplus
}
#endif		// __cplusplus
#endif /* LOGGER_H_ */
