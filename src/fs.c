/* -------------------------------------------------------------------------- */
/*                                  INCLUDES                                  */
/* -------------------------------------------------------------------------- */

#include "..\include\fs.h"
#include "..\include\logger.h"
#include <string.h>

/* -------------------------------------------------------------------------- */
/*                                   MACROS                                   */
/* -------------------------------------------------------------------------- */

#define MAX_STRING_BUFFER_SIZE 128

#define MODE_READ_BINARY "rb"
#define MODE_WRITE_BINARY "wb"

/* -------------------------------------------------------------------------- */
/*                                  TYPEDEFS                                  */
/* -------------------------------------------------------------------------- */

typedef struct _HFS {
    FILE* m_pFile;
    char m_szName[MAX_STRING_BUFFER_SIZE];
} HFS;

typedef struct _HFILE {
    char m_szName[MAX_STRING_BUFFER_SIZE];
    size_t m_iBaseOffset;
} HFILE;

/* -------------------------------------------------------------------------- */
/*                          FUNCTION IMPLEMENTATIONS                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------- EXPORTED -------------------------------- */

HFS* CreateFileSystemDriverInstance(const char* szFSRootPath)
{
    if(szFSRootPath == NULL)
    {
        LogWarning(_DEBUG_MSG("Invalid name passed for FileSystem instance!"));
        goto error;
    }
    
    HFS* pFileSystemHandle = malloc(sizeof(HFS));

    if(pFileSystemHandle == NULL)
    {
        LogWarning(_DEBUG_MSG("Could not malloc space for FileSystem driver!"));
        goto error;
    }

    strncpy(pFileSystemHandle->m_szName, szFSRootPath, MAX_STRING_BUFFER_SIZE);

    pFileSystemHandle->m_pFile = fopen(pFileSystemHandle->m_szName, MODE_READ_BINARY);
    if(pFileSystemHandle->m_pFile == NULL)
    {
        LogWarning(_DEBUG_MSG("Could not open specified FileSystem file in \"" MODE_READ_BINARY "\" mode."));
        goto error;
    }

    return pFileSystemHandle;

error:
    if(pFileSystemHandle != NULL)
    {
        if(pFileSystemHandle->m_pFile != NULL)
        {
            fclose(pFileSystemHandle->m_pFile);
        }
        free(pFileSystemHandle);
    }
    return NULL;
}

ERROR_E DestroyFileSystemDriverInstance(HFS* pFSHandle)
{
    return NOK;
}

HFILE* OpenFile(HFS* pFSHandle, const char* szFileName)
{
    return NULL;
}

ERROR_E CloseFile(HFS* pFSHandle, HFILE* pFileHandle)
{
    return NOK;
}

size_t ReadFile(HFILE* pFileHandle, size_t iBufferLength, OUT uint8_t* pBuffer)
{
    return 0;
}

size_t WriteFile(HFILE* pFileHandle, size_t iBufferLength, uint8_t* pBuffer)
{
    return 0;
}
