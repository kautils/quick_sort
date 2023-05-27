
#ifndef KAUTIL_SHAREDLIB_NOLINK_H
#define KAUTIL_SHAREDLIB_NOLINK_H

#include "./protocol.h"


// in terms of this lib extern "C" is needed
extern "C" __kautil_shared_prefix kautil_nolink_handler * kautil_nolink_initialize(const char path_to_shared_lib[], int const &flags);
extern "C" __kautil_shared_prefix void kautil_nolink_finalize(kautil_nolink_handler *hdl);
extern "C" __kautil_shared_prefix const char *  kautil_nolink_error_sentence(kautil_nolink_handler * hdl);


#endif
