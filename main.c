#include <stdlib.h>
#include "include/logger.h"

int main()
{
    
    HLOGGER* pLogger = CreateLoggerInstance(LOG_VERBOSITY_DEBUG);
    if(pLogger == NULL)
    {
        exit(-1);
    }


    ERROR_E err = LogDebug(pLogger, "This is an example test message!");
    err = LogInfo(pLogger, "Example info message.");


    DestroyLoggerInstance(pLogger);

    system("PAUSE");
}