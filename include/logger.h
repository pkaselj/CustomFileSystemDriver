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

ERROR_E InitializeLogger();
ERROR_E DeinitializeLogger();
ERROR_E SetLoggerLevel(LOG_LEVEL_FLAGS fLogLevel);

ERROR_E LogWarning(const char* message);
ERROR_E LogError(const char* message);
ERROR_E LogInfo(const char* message);
ERROR_E LogDebug(const char* message);
ERROR_E LogSuccess(const char* message);

#endif // !LOGGER_H
