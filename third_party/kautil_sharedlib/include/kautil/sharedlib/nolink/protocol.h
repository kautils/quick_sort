#ifndef KAUTIL_NOLINK_PROTOCOL_H
#define KAUTIL_NOLINK_PROTOCOL_H

#include "../common.h"
#include <stdint.h>


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



#define KAUTIL_NOLINK_FAIL_TO_LOAD_FUNCTION_TABLE 1
#define KAUTIL_NOLINK_FAIL_TO_LOAD_INIIALIZE_IMPLE 2
#define KAUTIL_NOLINK_FAIL_TO_LOAD_VERSION_IMPLE 4
#define KAUTIL_NOLINK_FAIL_TO_LOAD_FINALIZE_IMPLE 8


#define KAUTIL_VERSION_TABLE_ATTR_STRUCT __attribute__((packed,aligned(8)))
#define KAUTIL_SHAREDLIB_xstr(v) KAUTIL_SHAREDLIB_str(v)
#define KAUTIL_SHAREDLIB_str(v) #v
//https://gcc.gnu.org/onlinedocs/cpp/Stringizing.html

///@brief protocol for using nolink

using kautil_nolink_initialize_imple_t = void *(*)(void * dlhandler);
using kautil_nolink_finalize_imple_t = void (*)(void * f_table);
using kautil_nolink_version_imple_t = uint64_t (*)();


#define KAUTIL_NOLINK_INITIALIZE_IMPLE kautil_nolink_initialize_implementation
#define KAUTIL_NOLINK_INITIALIZE_IMPLE_NAME KAUTIL_SHAREDLIB_xstr(KAUTIL_NOLINK_INITIALIZE_IMPLE)
#define KAUTIL_NOLINK_INITIALIZE_IMPLE_TYPE_CHECK static kautil_nolink_initialize_imple_t kTestKautilNolinkInitializeImpleT = KAUTIL_NOLINK_INITIALIZE_IMPLE;

#define KAUTIL_NOLINK_FINALIZE_IMPLE kautil_nolink_finalize_implementation
#define KAUTIL_NOLINK_FINALIZE_IMPLE_NAME KAUTIL_SHAREDLIB_xstr(KAUTIL_NOLINK_FINALIZE_IMPLE)
#define KAUTIL_NOLINK_FINALIZE_IMPLE_TYPE_CHECK static kautil_nolink_finalize_imple_t kTestKautilNolinkFinalizeImpleT = KAUTIL_NOLINK_FINALIZE_IMPLE;

#define KAUTIL_NOLINK_VERSION_IMPLE kautil_nolink_version_implementation
#define KAUTIL_NOLINK_VERSION_IMPLE_NAME KAUTIL_SHAREDLIB_xstr(KAUTIL_NOLINK_VERSION_IMPLE)
#define KAUTIL_NOLINK_VERSION_IMPLE_TYPE_CHECK static kautil_nolink_version_imple_t kTestKautilNolinkVersionImpleT = KAUTIL_NOLINK_VERSION_IMPLE;


#define KAUTIL_NOLINK_IS_IMPLED_ALL\
    static auto kImple##KAUTIL_NOLINK_INITIALIZE_IMPLE = KAUTIL_NOLINK_INITIALIZE_IMPLE;\
    static auto kImple##KAUTIL_NOLINK_FINALIZE_IMPLE = KAUTIL_NOLINK_FINALIZE_IMPLE;\
    static auto kImple##KAUTIL_NOLINK_VERSION_IMPLE = KAUTIL_NOLINK_VERSION_IMPLE;


//todo : bad
//kautil_nolink_handler
//kautil_nolink_ft
// is too similar. cause confusion

struct kautil_nolink_handler {
    void *dl_handle = nullptr;
    void *function_table = nullptr;
    kautil_nolink_version_imple_t version = nullptr;
    kautil_nolink_initialize_imple_t initializer = nullptr;
    kautil_nolink_finalize_imple_t finalizer = nullptr;
    int error_code=0;
}/*    __attribute__((packed, aligned(8)))*/;


/// @brief nolink it's self
using kautil_nolink_initialize_t = kautil_nolink_handler * (*)(const char path_to_shared_lib[], int const &flags);
using kautil_nolink_finalize_t = void (*)(kautil_nolink_handler *hdl);
using kautil_nolink_error_sentence_t = const char *  (*)(kautil_nolink_handler * hdl);

struct kautil_nolink_ft{
    kautil_nolink_initialize_t initialize = nullptr;
    kautil_nolink_finalize_t finalize = nullptr;
    kautil_nolink_error_sentence_t error_sentence = nullptr;
    void * dl_handle = nullptr;
};

#ifdef KAUTIL_NOLINK_SO
kautil_nolink_ft * kautil_nolink_initialize_self();
#endif
kautil_nolink_ft * kautil_nolink_initialize_self(void * nolink_hdl);
void kautil_nolink_finalize_self(kautil_nolink_ft * ft);





#endif


