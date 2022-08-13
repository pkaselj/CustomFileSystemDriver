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

    FS_ERROR error = FS_InitializeErrorContainer();
    HFS* pFileSystemHandle = FS_CreateFileSystemDriverInstance(NULL, &error);
    if(FS_IsError(error))
    {
        char const * szErrorMsg = FS_GetErrorInfoString(error);
        // LogWarning(_DEBUG_MSG(szErrorMsg));
        LogWarning(szErrorMsg);
    }


    DeinitializeLogger();

    system("PAUSE");
}