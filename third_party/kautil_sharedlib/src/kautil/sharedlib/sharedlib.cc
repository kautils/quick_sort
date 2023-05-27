#include "../../../include/kautil/sharedlib/nolink/nolink.h"
#include "../../../include/kautil/sharedlib/sharedlib.h"


#if defined(WIN32) || defined(WIN64) || defined(_MSC_VER)

#include "./msvc_bypass_c1189.h"
#include <libloaderapi.h>
#include <errhandlingapi.h>

int rtld_lazy = 0;
int rtld_now = 1;
int rtld_global = 2;
int rtld_local = 4;
int rtld_nodelete = 8;
int rtld_noload = 16;
int rtld_deepbind = 32;


__kautil_shared_prefix void* kautil_dlopen(const char * path_to_shared_lib, int flags) { return LoadLibraryA((char*)path_to_shared_lib); }
__kautil_shared_prefix void* kautil_dlsym(void * handle, const char *symbol) { return (void *) GetProcAddress(reinterpret_cast<HMODULE>(handle),(char *)symbol); }
__kautil_shared_prefix int kautil_dlclose(void * handle) { return FreeLibrary(reinterpret_cast<HMODULE>(handle));}
#else

#include <dlfcn.h>
int rtld_lazy = RTLD_LAZY;
int rtld_now = RTLD_NOW;
int rtld_global = RTLD_GLOBAL;
int rtld_local = RTLD_LOCAL;
int rtld_nodelete = RTLD_NODELETE;
int rtld_noload = RTLD_NOLOAD;
int rtld_deepbind = RTLD_DEEPBIND;

void* kautil_dlopen(const char * path_to_shared_lib, int flags) { return dlopen(path_to_shared_lib,flags); }
void* kautil_dlsym(void * handle, const char *symbol) { return (void *) dlsym(handle,(char *)symbol); }
int kautil_dlclose(void * handle) { return dlclose(handle); }

#endif


#include "../../../include/kautil/sharedlib/nolink/nolink.h"

#ifdef KAUTIL_NOLINK_SO
kautil_nolink_ft * kautil_nolink_initialize_self(){
    return kautil_nolink_initialize_self(__dlopen(KAUTIL_NOLINK_SO,rtld_lazy|rtld_nodelete));
}
#endif


#include <iostream>

kautil_nolink_ft * kautil_nolink_initialize_self(void * dl_handle){
    auto ft = new kautil_nolink_ft{};
    ft->dl_handle = dl_handle;
    ft->initialize = __dlsym(ft->dl_handle,kautil_nolink_initialize);
    ft->finalize = __dlsym(ft->dl_handle, kautil_nolink_finalize);
    ft->error_sentence = __dlsym(ft->dl_handle, kautil_nolink_error_sentence);
    return ft;
}

void kautil_nolink_finalize_self(kautil_nolink_ft * ft){
    __dlclose(ft->dl_handle);
    delete reinterpret_cast<kautil_nolink_ft*>(ft);
}



static void __compile_time_check(){


    #define KAUTIL_NOLINK_TYPE_CHECK(obj,name) obj.name = (decltype(kautil_nolink_##name)*) nullptr;
    #define KAUTIL_ABFT_TYPE_CHECK(obj,name) obj.name = (decltype(kautil_##name)*) nullptr;

    auto test = kautil_nolink_ft{};
    KAUTIL_NOLINK_TYPE_CHECK(test,initialize);
    KAUTIL_NOLINK_TYPE_CHECK(test,finalize);
    #undef KAUTIL_ABFT_TYPE_CHECK
    #undef KAUTIL_NOLINK_TYPE_CHECK
}



#ifdef _MSC_VER
#include <iostream>
//#include <istream>
#else

// !!!!!!!!!!!!!!!!!!!!! never comment out iostream
// !!!!!!!!!!!!!!!!!!!!! static ios_base::Init __ioinit; // lack of this may cause exit(3)
#include <bits/ios_base.h>	// For ios_base declarations.
// !!!!!!!!!!!!!!!!!!!!!
// !!!!!!!!!!!!!!!!!!!!!
#endif


