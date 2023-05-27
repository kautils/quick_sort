#include "../../../include/kautil/sharedlib/sharedlib.h"
#include "../../../include/kautil/sharedlib/nolink/nolink.h"




extern "C"{

__kautil_shared_prefix kautil_nolink_handler * kautil_nolink_initialize(const char path_to_shared_lib[],int const& flags){


        auto hdl = __dlopen(path_to_shared_lib,flags);
        auto nolink_initialize = (kautil_nolink_initialize_imple_t) kautil_dlsym(hdl,KAUTIL_NOLINK_INITIALIZE_IMPLE_NAME);
        auto res = new kautil_nolink_handler;{
            res-> dl_handle=hdl;
            res->function_table=nolink_initialize ? nolink_initialize(hdl) : nullptr;
            res->version=(kautil_nolink_version_imple_t) kautil_dlsym(hdl,KAUTIL_NOLINK_VERSION_IMPLE_NAME);
            res->initializer=nolink_initialize;
            res->finalizer=(kautil_nolink_finalize_imple_t) kautil_dlsym(hdl,KAUTIL_NOLINK_FINALIZE_IMPLE_NAME);
            res->error_code=0;
        }

        if(!nolink_initialize) res->error_code |= KAUTIL_NOLINK_FAIL_TO_LOAD_FUNCTION_TABLE;
        if(!res->initializer) res->error_code |=KAUTIL_NOLINK_FAIL_TO_LOAD_INIIALIZE_IMPLE;
        if(!res->finalizer) res->error_code |=KAUTIL_NOLINK_FAIL_TO_LOAD_VERSION_IMPLE;
        if(!res->version) res->error_code |=KAUTIL_NOLINK_FAIL_TO_LOAD_FINALIZE_IMPLE;


        return res;
    }


__kautil_shared_prefix const char *  kautil_nolink_error_sentence(kautil_nolink_handler * hdl){
    if(hdl->error_code & KAUTIL_NOLINK_FAIL_TO_LOAD_FUNCTION_TABLE){
        static const char * str = "kautil_nolink_fail_to_load_function_table";
        hdl->error_code ^=KAUTIL_NOLINK_FAIL_TO_LOAD_FUNCTION_TABLE;
        return str;
    }
    if(hdl->error_code & KAUTIL_NOLINK_FAIL_TO_LOAD_INIIALIZE_IMPLE){
        static const char * str = "kautil_nolink_fail_to_load_inialize_imple";
        hdl->error_code ^=KAUTIL_NOLINK_FAIL_TO_LOAD_INIIALIZE_IMPLE;
        return str;
    }
    if(hdl->error_code & KAUTIL_NOLINK_FAIL_TO_LOAD_VERSION_IMPLE){
        static const char * str = "kautil_nolink_fail_to_load_version_imple";
        hdl->error_code ^=KAUTIL_NOLINK_FAIL_TO_LOAD_VERSION_IMPLE;
        return str;
    }
    if(hdl->error_code & KAUTIL_NOLINK_FAIL_TO_LOAD_FINALIZE_IMPLE){
        static const char * str = "kautil_nolink_fail_to_load_finalize_imple";
        hdl->error_code ^=KAUTIL_NOLINK_FAIL_TO_LOAD_FINALIZE_IMPLE;
        return str;
    }
    return nullptr;
}



__kautil_shared_prefix void kautil_nolink_finalize(kautil_nolink_handler * hdl){
    if(hdl) {
        hdl->finalizer(hdl->function_table);
        __dlclose(hdl->dl_handle);
        delete hdl;
    }
}



} // extern "C"