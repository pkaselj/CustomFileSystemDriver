#ifndef FS_H
#define FS_H

#include "common_libs.h"
#include "common.h"

#include <stdint.h>

typedef struct _HFS HFS;
typedef struct _HFILE HFILE;

HFS*    CreateFileSystemDriverInstance(const char* szFSRootPath);
ERROR_E DestroyFileSystemDriverInstance(HFS* pFSHandle);

ERROR_E OpenFile(HFS* pFSHandle, const char* szFileName, OUT HFILE** pFileHandleContainer);
ERROR_E CloseFile(HFS* pFSHandle, HFILE* pFileHandle);

// Returns bytes read
size_t ReadFile(HFILE* pFileHandle, size_t iBufferLength, OUT uint8_t* pBuffer);

// Returns bytes written
size_t WriteFile(HFILE* pFileHandle, size_t iBufferLength, uint8_t* pBuffer);

#endif