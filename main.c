#include "include/common_libs.h"
#include "include/logger.h"
#include "include/fs.h"

int main()
{
    
    ERROR_E err = InitializeLogger(LOG_VERBOSITY_DEBUG);
    if(err != OK)
    {
        exit(-1);
    }


    err = LogDebug("This is an example test message!");
    err = LogInfo("Example info message.");

    HFS* pFileSystemHandle = CreateFileSystemDriverInstance(NULL);


    DeinitializeLogger();

    system("PAUSE");
}