#ifndef KAUTIL_SHAREDLIB_NOLINK_VERSION_TABLE_H
#define KAUTIL_SHAREDLIB_NOLINK_VERSION_TABLE_H

#include <stdint.h>


extern "C"{

void * kautil_version_table_initialize();
void kautil_version_table_finalize(void * hdl);
void kautil_version_table_push(void * hdl,uint64_t const& version,void * function_table,void * object );

uint64_t * kautil_version_table_version(void * hdl);
void ** kautil_version_table_object(void * hdl);
void ** kautil_version_table_functions(void * hdl);

};


#endif