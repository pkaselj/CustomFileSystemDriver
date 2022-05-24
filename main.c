#include "include/common_libs.h"
#include "include/logger.h"

int main()
{
    
    ERROR_E err = InitializeLogger(LOG_VERBOSITY_DEBUG);
    if(err != OK)
    {
        exit(-1);
    }


    err = LogDebug("This is an example test message!");
    err = LogInfo("Example info message.");


    DeinitializeLogger();

    system("PAUSE");
}