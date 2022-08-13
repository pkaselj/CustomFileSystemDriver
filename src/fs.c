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
/*                        PRIVATE FUNCTIONS                                   */
/* -------------------------------------------------------------------------- */

PRIVATE void _SetError(FS_ERROR * pErrorContainer, FS_ERROR error_value)
{
    if (NULL == pErrorContainer)
    {
        return;
    }

    *pErrorContainer = error_value;
}

/* -------------------------------------------------------------------------- */
/*                          FUNCTION IMPLEMENTATIONS                          */
/* -------------------------------------------------------------------------- */

/* -------------------------------- EXPORTED -------------------------------- */

HFS* FS_CreateFileSystemDriverInstance(const char* szFSRootPath, OPTIONAL FS_ERROR * pErrorContainer)
{
    HFS* pFileSystemHandle = NULL; // Required because of error handling goto
    FS_ERROR current_error_value = FS_ERROR_ok; // Default value. Set to error during
                                                // function execution and return to caller
                                                // using OPTIONAL FS_ERROR * pErrorContainer

    if(szFSRootPath == NULL)
    {
        current_error_value = FS_ERROR_invalid_filename;
        goto cleanup;
    }
    
    pFileSystemHandle = malloc(sizeof(HFS));

    if(pFileSystemHandle == NULL)
    {
        current_error_value = FS_ERROR_malloc_error;
        goto cleanup;
    }

    strncpy(pFileSystemHandle->m_szName, szFSRootPath, MAX_STRING_BUFFER_SIZE);

    pFileSystemHandle->m_pFile = fopen(pFileSystemHandle->m_szName, MODE_READ_BINARY);
    if(pFileSystemHandle->m_pFile == NULL)
    {
        current_error_value = FS_ERROR_open_failed;
        goto cleanup;
    }

    return pFileSystemHandle;

cleanup:
    FS_DestroyFileSystemDriverInstance(pFileSystemHandle, NULL);
    _SetError(pErrorContainer, current_error_value);
    return NULL;
}

void FS_DestroyFileSystemDriverInstance(HFS* pFSHandle, OPTIONAL FS_ERROR * pErrorContainer)
{
    if(NULL != pFSHandle)
    {
        if(NULL != pFSHandle->m_pFile)
        {
            fclose(pFSHandle->m_pFile);
        }
        free(pFSHandle);
    }

    _SetError(pErrorContainer, FS_ERROR_ok);
}

HFILE* FS_OpenFile(HFS* pFSHandle, const char* szFileName, OPTIONAL FS_ERROR * pErrorContainer)
{
    _SetError(pErrorContainer, FS_ERROR_not_implemented);
    return NULL;
}

void FS_CloseFile(HFS* pFSHandle, HFILE* pFileHandle, OPTIONAL FS_ERROR * pErrorContainer)
{
    _SetError(pErrorContainer, FS_ERROR_not_implemented);
}

size_t FS_ReadFile(HFILE* pFileHandle, size_t iBufferLength, OUT uint8_t* pBuffer, OPTIONAL FS_ERROR * pErrorContainer)
{
    _SetError(pErrorContainer, FS_ERROR_not_implemented);
    return 0;
}

size_t FS_WriteFile(HFILE* pFileHandle, size_t iBufferLength, uint8_t* pBuffer, OPTIONAL FS_ERROR * pErrorContainer)
{
    _SetError(pErrorContainer, FS_ERROR_not_implemented);
    return 0;
}

bool FS_IsError(FS_ERROR error_value)
{
    return (FS_ERROR_ok != error_value);
}

FS_ERROR FS_InitializeErrorContainer(void)
{
    return FS_ERROR_ok;
}

char const * FS_GetErrorInfoString(FS_ERROR error_value)
{
    switch (error_value)
    {
    case FS_ERROR_ok:                   return "FS :: No error, action executed successfully";
    case FS_ERROR_general_error:        return "FS :: General error";
    case FS_ERROR_not_implemented:      return "FS :: Function not implemented";
    case FS_ERROR_invalid_filename:     return "FS :: Invalid file name";
    case FS_ERROR_malloc_error:         return "FS :: Could not malloc space for FileSystem driver handle!";
    case FS_ERROR_open_failed:          return "FS :: Could not open specified FileSystem file";
    }

    return "FS :: INVALID_ERROR_CODE";
}

