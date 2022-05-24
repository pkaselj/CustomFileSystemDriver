#include "..\include\fs.h"

#define MAX_STRING_BUFFER_SIZE 128

typedef struct _HFS {
    FILE* m_pFile;
    char* m_szName[MAX_STRING_BUFFER_SIZE];
} HFS;

typedef struct _HFILE {
    char* m_szName[MAX_STRING_BUFFER_SIZE];
    size_t m_iBaseOffset;
} HFILE;

HFS* CreateFileSystemDriverInstance(const char* szFSRootPath)
{
    if(szFSRootPath == NULL)
    {
        return NULL;
    }
    return NULL;
}

ERROR_E DestroyFileSystemDriverInstance(HFS* pFSHandle)
{
    return NOK;
}

ERROR_E OpenFile(HFS* pFSHandle, const char* szFileName, OUT HFILE** pFileHandleContainer)
{
    return NOK;
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