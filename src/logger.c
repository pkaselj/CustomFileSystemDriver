/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */

#include "../include/logger.h"
#include "../include/common_libs.h"

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

#define DEFAULT_LOG_LEVEL LOG_VERBOSITY_DEBUG

#define ISSET(FLAGS, LOG_FLAG) ((FLAGS & ~LOG_FLAG) != 0) 

/* -------------------------------------------------------------------------- */
/*                                  TYPEDEFS                                  */
/* -------------------------------------------------------------------------- */

typedef struct _HLOGGER HLOGGER;
typedef ERROR_E (*FNPPRINT) (const char*);

typedef struct _HLOGGER {
    FNPPRINT m_fnWarning;
    FNPPRINT m_fnInfo;
    FNPPRINT m_fnSuccess;
    FNPPRINT m_fnDebug;
    FNPPRINT m_fnError;
} HLOGGER;

/* -------------------------------------------------------------------------- */
/*                            FUNCTION DEFINITIONS                            */
/* -------------------------------------------------------------------------- */


/* --------------------------------- PRIVATE -------------------------------- */

PRIVATE ERROR_E _InitializeLogger_wLevel(LOG_LEVEL_FLAGS fLogLevel);
PRIVATE void _Success(const char* message);
PRIVATE void _Print(const char* prefix, const char* message);
PRIVATE HLOGGER* CreateLoggerInstance(LOG_LEVEL_FLAGS fLevel);
PRIVATE ERROR_E DestroyLoggerInstance(HLOGGER* pHandle);
PRIVATE void _Warning(const char* message);
PRIVATE void _Error(const char* message);
PRIVATE void _Info(const char* message);
PRIVATE void _Debug(const char* message);

/* -------------------------------------------------------------------------- */
/*                                   GLOBALS                                  */
/* -------------------------------------------------------------------------- */

GLOBAL PRIVATE HLOGGER* g_pLogger; 


/* -------------------------------------------------------------------------- */
/*                           FUNCTION IMPLEMENTATION                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------- EXPORTED -------------------------------- */


ERROR_E InitializeLogger()
{
    return _InitializeLogger_wLevel(DEFAULT_LOG_LEVEL);
}

ERROR_E DeinitializeLogger()
{
    return DestroyLoggerInstance(g_pLogger);
}

ERROR_E SetLoggerLevel(LOG_LEVEL_FLAGS fLogLevel)
{
    ERROR_E err = DeinitializeLogger();
    if(err != OK)
    {
        return err;
    }

    return _InitializeLogger_wLevel(fLogLevel);
}

ERROR_E LogSuccess(const char* message)
{
    if(g_pLogger == NULL || g_pLogger->m_fnSuccess == NULL)
    {
        return NOK;
    }

    _Success(message);

    return OK;
}

ERROR_E LogDebug(const char* message)
{
    if(g_pLogger == NULL || g_pLogger->m_fnDebug == NULL)
    {
        return NOK;
    }

    _Debug(message);

    return OK;
}

ERROR_E LogInfo(const char* message)
{
    if(g_pLogger == NULL || g_pLogger->m_fnInfo == NULL)
    {
        return NOK;
    }

    _Info(message);

    return OK;
}

ERROR_E LogWarning(const char* message)
{
    if(g_pLogger == NULL || g_pLogger->m_fnWarning == NULL)
    {
        return NOK;
    }

    _Warning(message);

    return OK;
}

ERROR_E LogError(const char* message)
{
    if(g_pLogger == NULL || g_pLogger->m_fnError == NULL)
    {
        return NOK;
    }

    _Error(message);
    exit(-1);

    return OK;
}

/* --------------------------------- PRIVATE -------------------------------- */

PRIVATE ERROR_E _InitializeLogger_wLevel(LOG_LEVEL_FLAGS fLogLevel)
{
    g_pLogger = CreateLoggerInstance(LOG_VERBOSITY_DEBUG);
    if(g_pLogger == NULL)
    {
        return NOK;
    }
    return OK;
}

PRIVATE HLOGGER* CreateLoggerInstance(LOG_LEVEL_FLAGS fLevel)
{
    HLOGGER* pHandle = (HLOGGER*) malloc(sizeof(HLOGGER));

    if(pHandle == NULL)
    {
        return NULL;
    }

    pHandle->m_fnWarning =  (ISSET(fLevel, WARNING) ? &LogWarning   : NULL);
    pHandle->m_fnError   =  &LogError;  // Non maskable
    pHandle->m_fnInfo    =  (ISSET(fLevel, INFO)    ? &LogInfo      : NULL);
    pHandle->m_fnSuccess =  (ISSET(fLevel, SUCCESS) ? &LogSuccess   : NULL);
    pHandle->m_fnDebug   =  (ISSET(fLevel, DEBUG)   ? &LogDebug     : NULL);

    return pHandle;

}

PRIVATE ERROR_E DestroyLoggerInstance(HLOGGER* pHandle)
{
    if(pHandle == NULL)
    {
        return NOK;
    }

    free(pHandle);

    return OK;
}

PRIVATE void _Warning(const char* message)
{
    _Print("WARNING", message);
}


PRIVATE void _Error(const char* message)
{
    _Print("ERROR", message);
}


PRIVATE void _Info(const char* message)
{
    _Print("INFO", message);
}


PRIVATE void _Debug(const char* message)
{
    _Print("DEBUG", message);
}


PRIVATE void _Success(const char* message)
{
    _Print("SUCCESS", message);
}

PRIVATE void _Print(const char* prefix, const char* message)
{
    printf("[%s] :: %s\n", prefix, message);
}