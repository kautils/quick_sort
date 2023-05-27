

#include "kautil/sharedlib/version_table/protocol.h"
#include "kautil/sharedlib/sharedlib.h"
#include "kautil/sharedlib/nolink/protocol.h"
#include <vector>

struct kautil_version_table{
    std::vector<uint64_t> version;
    std::vector<void*> object;
    std::vector<void*> function_table;
};

#define __vt(hdl) reinterpret_cast<kautil_version_table*>(hdl)

extern "C"{

void * kautil_version_table_initialize(){ return new kautil_version_table{}; }
void kautil_version_table_finalize(void * hdl){ delete __vt(hdl); }

uint64_t * kautil_version_table_version(void * hdl){ return __vt(hdl)->version.data(); }
void ** kautil_version_table_object(void * hdl){ return __vt(hdl)->object.data(); }
void ** kautil_version_table_function_table(void * hdl){ return __vt(hdl)->function_table.data(); }
uint64_t kautil_version_table_size(void * hdl){
    return __vt(hdl)->version.size();
}

void kautil_version_table_push(void * hdl,uint64_t const& version,void * function_table,void * object){
    auto const& vt = reinterpret_cast<kautil_version_table*>(hdl);
     vt->version.push_back(version);
    vt->function_table.push_back(function_table);
    vt->object.push_back(object);
}


void * KAUTIL_NOLINK_INITIALIZE_IMPLE(void * dl_handler){
    auto res = new kautil_version_table_ft{};
    res->initialize = __dlsym(dl_handler,kautil_version_table_initialize);
    res->finalize = __dlsym(dl_handler,kautil_version_table_finalize);
    res->push = __dlsym(dl_handler,kautil_version_table_push);
    res->object = __dlsym(dl_handler, kautil_version_table_object);
    res->version = __dlsym(dl_handler, kautil_version_table_version);
    res->function_table = __dlsym(dl_handler, kautil_version_table_function_table);
    res->size = __dlsym(dl_handler, kautil_version_table_size);
    return res;
}
void KAUTIL_NOLINK_FINALIZE_IMPLE(void * hdl){ delete reinterpret_cast<kautil_version_table_ft*>(hdl); }
uint64_t KAUTIL_NOLINK_VERSION_IMPLE(){ return static_cast<uint64_t>(KAUTIL_VERSION_TABLE_VERSION); }


KAUTIL_NOLINK_INITIALIZE_IMPLE_TYPE_CHECK
KAUTIL_NOLINK_FINALIZE_IMPLE_TYPE_CHECK
KAUTIL_NOLINK_VERSION_IMPLE_TYPE_CHECK
KAUTIL_NOLINK_IS_IMPLED_ALL


} // extern "C"
