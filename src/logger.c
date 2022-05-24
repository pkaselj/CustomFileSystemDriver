#include "../include/logger.h"

#include <stdio.h>
#include <stdlib.h>

#define ISSET(FLAGS, LOG_FLAG) ((FLAGS & ~LOG_FLAG) != 0) 

typedef ERROR_E (*FNPPRINT) (HLOGGER*, const char*);

typedef struct _HLOGGER {
    FNPPRINT m_fnWarning;
    FNPPRINT m_fnInfo;
    FNPPRINT m_fnSuccess;
    FNPPRINT m_fnDebug;
    FNPPRINT m_fnError;
} HLOGGER;

void _Warning(const char* message);
void _Error(const char* message);
void _Info(const char* message);
void _Debug(const char* message);
void _Success(const char* message);
void _Print(const char* prefix, const char* message);

HLOGGER* CreateLoggerInstance(LOG_LEVEL_FLAGS fLevel)
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

ERROR_E DestroyLoggerInstance(HLOGGER* pHandle)
{
    if(pHandle == NULL)
    {
        return NOK;
    }

    free(pHandle);

    return OK;
}

ERROR_E LogWarning(HLOGGER* pHandle, const char* message)
{
    if(pHandle == NULL || pHandle->m_fnWarning == NULL)
    {
        return NOK;
    }

    _Warning(message);

    return OK;
}

void _Warning(const char* message)
{
    _Print("WARNING", message);
}

ERROR_E LogError(HLOGGER* pHandle, const char* message)
{
    if(pHandle == NULL || pHandle->m_fnError == NULL)
    {
        return NOK;
    }

    _Error(message);
    exit(-1);

    return OK;
}

void _Error(const char* message)
{
    _Print("ERROR", message);
}

ERROR_E LogInfo(HLOGGER* pHandle, const char* message)
{
    if(pHandle == NULL || pHandle->m_fnInfo == NULL)
    {
        return NOK;
    }

    _Info(message);

    return OK;
}

void _Info(const char* message)
{
    _Print("INFO", message);
}

ERROR_E LogDebug(HLOGGER* pHandle, const char* message)
{
    if(pHandle == NULL || pHandle->m_fnDebug == NULL)
    {
        return NOK;
    }

    _Debug(message);

    return OK;
}

void _Debug(const char* message)
{
    _Print("DEBUG", message);
}

ERROR_E LogSuccess(HLOGGER* pHandle, const char* message)
{
    if(pHandle == NULL || pHandle->m_fnSuccess == NULL)
    {
        return NOK;
    }

    _Success(message);

    return OK;
}

void _Success(const char* message)
{
    _Print("SUCCESS", message);
}

void _Print(const char* prefix, const char* message)
{
    printf("[%s] :: %s\n", prefix, message);
}