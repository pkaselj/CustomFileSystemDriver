#ifndef COMMON_H
#define COMMON_H

#define IN
#define OUT

#define GLOBAL
#define PRIVATE static

#ifndef __FUNCTION__
#define __FUNCTION__ 
#endif // !__FUNCTION__


#define _AS_STR_PRIVATE(X) #X
#define _AS_STR(X) _AS_STR_PRIVATE(X)
#define _DEBUG_MSG(MSG)  " FUNC: " __FUNCTION__ " | FILE: " __FILE__ " | LINE: " _AS_STR(__LINE__) " >>> " MSG

#define BIT(X) 1 << X

typedef enum {
    OK = 0,
    NOK = 1
} ERROR_E;

#endif
