
#ifndef KAUTIL_SHAREDLIB_VERSION_TABLE_PROTOCOL_H
#define KAUTIL_SHAREDLIB_VERSION_TABLE_PROTOCOL_H

#include <stdint.h>

using kautil_version_table_push_t =  void (*)(void * hdl,uint64_t const& version,void * function_table,void * object);
using kautil_version_table_initialize_t = void * (*)();
using kautil_version_table_finalize_t = void (*)(void * hdl);

using kautil_version_table_version_t =  uint64_t * (*)(void * hdl);
using kautil_version_table_object_t = void ** (*)(void * hdl);
using kautil_version_table_functions_t = void ** (*)(void * hdl);
using kautil_version_table_size_t = uint64_t (*)(void * hdl);

struct kautil_version_table_ft{
    kautil_version_table_push_t push =  nullptr;
    kautil_version_table_initialize_t initialize = nullptr;
    kautil_version_table_finalize_t finalize = nullptr;
    kautil_version_table_version_t version =  nullptr;
    kautil_version_table_object_t object = nullptr;
    kautil_version_table_functions_t function_table  = nullptr;
    kautil_version_table_size_t size = nullptr;
};


#endif