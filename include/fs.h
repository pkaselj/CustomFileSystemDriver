#ifndef FS_H
#define FS_H

#include "common_libs.h"
#include "common.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct _HFS HFS;
typedef struct _HFILE HFILE;

typedef enum {
    FS_ERROR_ok = 0,
    FS_ERROR_general_error,
    FS_ERROR_not_implemented,
    FS_ERROR_invalid_filename,
    FS_ERROR_malloc_error,
    FS_ERROR_open_failed
} FS_ERROR;

// Use NULL to ignore OPTIONAL parameters

HFS*        FS_CreateFileSystemDriverInstance(char const * szFSRootPath, OPTIONAL FS_ERROR * pErrorContainer);
void        FS_DestroyFileSystemDriverInstance(HFS* pFSHandle, OPTIONAL FS_ERROR * pErrorContainer);

HFILE*      FS_OpenFile(HFS* pFSHandle, char const * szFileName, OPTIONAL FS_ERROR * pErrorContainer);
void        FS_CloseFile(HFS* pFSHandle, HFILE* pFileHandle, OPTIONAL FS_ERROR * pErrorContainer);

// Returns bytes read
size_t      FS_ReadFile(HFILE* pFileHandle, size_t iBufferLength, OUT uint8_t* pBuffer, OPTIONAL FS_ERROR * pErrorContainer);

// Returns bytes written
size_t      FS_WriteFile(HFILE* pFileHandle, size_t iBufferLength, uint8_t* pBuffer, OPTIONAL FS_ERROR * pErrorContainer);

// Error handling functions
char const * FS_GetErrorInfoString(FS_ERROR error_value);
bool         FS_IsError(FS_ERROR error_value);
FS_ERROR     FS_InitializeErrorContainer(void);

#endif