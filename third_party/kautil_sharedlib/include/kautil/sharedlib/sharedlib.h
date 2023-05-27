#ifndef KAUTIL_SHAREDLIB_SHAREDLIB_H
#define KAUTIL_SHAREDLIB_SHAREDLIB_H

#include "./common.h"

#ifdef _MSC_BUILD
    #ifdef KAUTIL_NOLINK_STATIC
        #define __kautil_shared_prefix
    #elif defined(KAUTIL_NOLINK_SHARED)
        #define __kautil_shared_prefix __declspec(dllexport)
    #else
        #define __kautil_shared_prefix __declspec(dllimport)
    #endif
#else
    #define __kautil_shared_prefix
#endif



__kautil_shared_prefix void* kautil_dlopen(const char * path_to_shared_lib,int flags);
__kautil_shared_prefix void* kautil_dlsym(void * handle, const char *symbol);
__kautil_shared_prefix int kautil_dlclose(void * handle);


#define __dlopen(path_to_shared_lib,flags) kautil_dlopen(path_to_shared_lib,flags)    /* future =>  load library ex  */
#define __dlsym(hdl,symname) (decltype(symname)*) kautil_dlsym(hdl,#symname)
#define __dlclose(hdl) kautil_dlclose(hdl)

#endif