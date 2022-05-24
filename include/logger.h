#ifndef LOGGER_H
#define LOGGER_H

#include "common.h"

typedef enum {
    INFO = BIT(0),
    WARNING = BIT(1),
    SUCCESS = BIT(2),
    DEBUG = BIT(3)
    // ERROR -- Non maskable
} LOG_LEVEL_FLAGS;

#define LOG_VERBOSITY_LOW       (WARNING | SUCCESS)
#define LOG_VERBOSITY_NORMAL    (WARNING | SUCCESS | INFO)
#define LOG_VERBOSITY_DEBUG     (WARNING | SUCCESS | INFO | DEBUG)

typedef struct _HLOGGER HLOGGER;

// LOG_LEVEL_FLAGS = INFO & WARNING
HLOGGER* CreateLoggerInstance(LOG_LEVEL_FLAGS fLevel);
ERROR_E DestroyLoggerInstance(HLOGGER* pHandle);

ERROR_E LogWarning(HLOGGER* pHandle, const char* message);
ERROR_E LogError(HLOGGER* pHandle, const char* message);
ERROR_E LogInfo(HLOGGER* pHandle, const char* message);
ERROR_E LogDebug(HLOGGER* pHandle, const char* message);
ERROR_E LogSuccess(HLOGGER* pHandle, const char* message);

#endif // !LOGGER_H
