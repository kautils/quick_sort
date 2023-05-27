
#ifndef KAUTIL_SHAREDLIB_COMMON_H
#define KAUTIL_SHAREDLIB_COMMON_H

/// @note on windows, some flags of them may be meaningless . currently i not implement yet
extern int rtld_lazy;
extern int rtld_now;
extern int rtld_global;
extern int rtld_local;
extern int rtld_nodelete;
extern int rtld_noload;
extern int rtld_deepbind;

#endif