
#include "../../include/kautil/algorithm/quick_sort/extern.h"
#include "kautil/algorithm/quick_sort/quick_sort.h"

#define hdl(o) reinterpret_cast<kautil_quick_sort_handle*>(o)

KAUTIL_QUICK_SORRT_PREFIX void *_kautil_quick_sort_initialize() { return kautil_quick_sort_initialize(); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_thread_arguments_alloc(void *hdl, const uint64_t &number_of_thread) { return kautil_quick_sort_thread_arguments_alloc(hdl(hdl),number_of_thread); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_thread_arguments_set(void *hdl, void *arg, const int &idx) { return kautil_quick_sort_thread_arguments_set(hdl(hdl),arg,idx); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_set_v2(void *hdl, const uint64_t &step,int (*cmp)(intptr_t, intptr_t, void *), void (*swap)(intptr_t, intptr_t, void *), intptr_t (*seek)(intptr_t, const int64_t &, void *)) { return kautil_quick_sort_set(hdl(hdl),step,cmp,swap,seek); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_set(void *hdl, const uint64_t &step, int (*cmp)(intptr_t, intptr_t, void *), void (*swap)(intptr_t, intptr_t, void *)) { return kautil_quick_sort_set(hdl(hdl),step,cmp,swap); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_intptr(void *hdl, intptr_t data_begin, intptr_t data_end) { return kautil_quick_sort(hdl(hdl),data_begin,data_end); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_sort_voidptr(void *hdl, const void *data_begin, const void *data_end) { return kautil_quick_sort(hdl(hdl),data_begin,data_end); }
KAUTIL_QUICK_SORRT_PREFIX int _kautil_quick_argument_set(void *hdl, void *arg) { return kautil_quick_argument_set(hdl(hdl),arg); }
KAUTIL_QUICK_SORRT_PREFIX void _kautil_quick_sort_finalize(void *hdl) { kautil_quick_sort_finalize(hdl(hdl)); }
